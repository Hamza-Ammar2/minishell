

#include "../include/minishell.h"
#include "../libft/libft.h"

extern t_sig g_sig;

static int strcmpy(const char *s1, const char *s2)
{
    size_t  i;

    if (!s1 || !s2)
        return (0);
    i = 0;
    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    if ((s1[i] == '\0' || s1[i] == '\n') && s2[i] == '\0')
        return (0);
    return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

static void sigint_handler_hd(int sig)
{
    (void)sig;
    write(STDOUT_FILENO, "\n", 1);
    close(g_sig.fd[0]);
    close(g_sig.fd[1]);
    exit(1);
}

static int heredoc(t_shell *shell, t_token *redir)
{
    char *line;
    int type;

    if (pipe(g_sig.fd) == -1)
        return (perror("heredoc pipe failed"), 0);
    if (dup2(shell->stdin_backup, STDIN_FILENO) == -1)
        return (perror("dup2 failed"), 0);
    signal(SIGINT, sigint_handler_hd);
    type = redir->quote_type;
    if (type == QUOTE_SINGLE || type == QUOTE_DOUBLE)
        type = QUOTE_SINGLE;
    line = expand_str(shell, readline("> "), type);
    while (strcmpy(line, redir->value) != 0)
    {
        write(g_sig.fd[1], line, strlen(line));
        write(g_sig.fd[1], "\n", 1);
        free(line);
        line = expand_str(shell, readline("> "), type);
        if (!line)
            break ;
    }
    if (dup2(g_sig.fd[0], STDIN_FILENO) == -1)
        return (perror("dup2 failed"), 0);
    return (close(g_sig.fd[1]), close(g_sig.fd[0]), free(line), 1);
}

static int    here_doc_app(t_shell *shell, t_token *redir)
{
    int file;

    if (redir->type == TOKEN_REDIRECT_APPEND)
    {
        if (dup2(shell->stdout_backup, STDOUT_FILENO) == -1)
            return (perror("dup2 failed"), 0);
        file = open(redir->value, O_WRONLY | O_APPEND | O_CREAT, 0644);
        if (file == -1)
            return (perror("could not open file"), 0);
        if (dup2(file, STDOUT_FILENO) == -1)
            return (perror("dup2 failed"), close(file), 0);
        close(file);
    }
    else if (redir->type == TOKEN_REDIRECT_HEREDOC)
    {
        if (!heredoc(shell, redir))
            return (0);
    }
    return (1);
}

static int  in_out(t_shell *shell, t_token *redir)
{
    int file;

    if (redir->type == TOKEN_REDIRECT_IN)
    {
        if (dup2(shell->stdin_backup, STDIN_FILENO) == -1)
            return (perror("dup2 failed"), 0);
        file = open(redir->value, O_RDONLY);
        if (file == -1)
            return (perror("could not open file"), 0);
        if (dup2(file, STDIN_FILENO) == -1)
            return (close(file), perror("dup2 failed"), 0);
        close(file);
    }
    else if (redir->type == TOKEN_REDIRECT_OUT)
    {
        if (dup2(shell->stdout_backup, STDOUT_FILENO) == -1)
            return (perror("dup2 failed"), 0);
        file = open(redir->value, O_WRONLY | O_TRUNC | O_CREAT, 0644);
        if (file == -1)
            return (perror("could not open file"), 0);
        if (dup2(file, STDOUT_FILENO) == -1)
            return (close(file), perror("dup2 failed"), 0);
        close(file);
    }
    return (1);
}

int    direct_io(t_shell *shell, t_command *cmd)
{
    t_token *redir;

    redir = cmd->redirects;
    while (redir)
    {
        if (redir->type == TOKEN_REDIRECT_IN || redir->type == TOKEN_REDIRECT_OUT)
        {
            if (!in_out(shell, redir))
                return (perror("direct_io failed"), 0);
        }
        else if (!here_doc_app(shell, redir))
            return (perror("direct_here_app failed"), 0);
        redir = redir->next;
    }
    return (1);
}
