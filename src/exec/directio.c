

#include "../include/minishell.h"
#include "../libft/libft.h"

extern sig_atomic_t sig;

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

static int clean_stuff(t_shell *shell, int fd[2], char *line)
{
    sig = 0;
    (void)shell;
    restore(shell);
    close(fd[1]);
    close(fd[0]);
    free(line);
    return (2);
}

static int heredoc(t_shell *shell, t_token *redir)
{
    char *line;
    int fd[2];
    int type;

    if (pipe(fd) == -1)
        return (perror("heredoc pipe failed"), 0);
    if (dup2(shell->stdin_backup, STDIN_FILENO) == -1)
        return (perror("dup2 failed"), 0);
    type = redir->quote_type;
    if (type == QUOTE_SINGLE || type == QUOTE_DOUBLE)
        type = QUOTE_SINGLE;
    line = expand_str(shell, readline("> "), type);
    if (sig)
        return (clean_stuff(shell, fd, line));
    while (strcmpy(line, redir->value) != 0)
    {
        write(fd[1], line, ft_strlen(line));
        write(fd[1], "\n", 1);
        free(line);
        line = expand_str(shell, readline("> "), type);
        if (sig)
            return (clean_stuff(shell, fd, line));
        if (!line)
            break ;
    }
    if (dup2(fd[0], STDIN_FILENO) == -1)
        return (close(fd[1]), close(fd[0]), perror("dup2 failed"), 0);
    return (close(fd[1]), close(fd[0]), free(line), 1);
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
        return (heredoc(shell, redir));
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
    int     hd;

    redir = cmd->redirects;
    while (redir)
    {
        if (redir->type == TOKEN_REDIRECT_IN || redir->type == TOKEN_REDIRECT_OUT)
        {
            if (!in_out(shell, redir))
                return (perror("direct_io failed"), 0);
            redir = redir->next;
            continue;
        }
        hd = here_doc_app(shell, redir);
        if (hd != 1)
        {
            if (!hd)
                perror("direct_here_app failed");
            return (0);
        }
        redir = redir->next;
    }
    return (1);
}
