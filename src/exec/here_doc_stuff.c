
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
    restore(shell);
    close(fd[1]);
    close(fd[0]);
    free(line);
    return (2);
}

static char *get_exp(t_shell *shell, char *value, int type)
{
    char *line;
    char    *raw;

    if (!isatty(STDIN_FILENO))
        raw = get_next_line(STDIN_FILENO);
    else
        raw = readline("> ");
    if (!raw)
        return (NULL);
    if (strcmpy(raw, value) == 0)
        return (free(raw), NULL);
    line = expand_quo(shell, raw, type);
    if (sig)
    {
        free(raw);
        return (NULL);
    }
    free(raw);
    return (line);
}

static int  here_doc_read(t_shell *shell, char *value, int type, int fd[2])
{
    char *line;

    // FIX: In non-interactive mode, heredocs can't work properly because stdin is shared
    // between main loop and heredoc reading. Skip heredoc and create empty pipe.
    line = get_exp(shell, value, type);
    if (sig)
        return (clean_stuff(shell, fd, line));
    while (strcmpy(line, value) != 0)
    {
        write(fd[1], line, ft_strlen(line));
        if (isatty(STDIN_FILENO))
            write(fd[1], "\n", 1);
        free(line);
        line = get_exp(shell, value, type);
        if (sig)
            return (clean_stuff(shell, fd, line));
        if (!line)
            break ;
    }
    if (dup2(fd[0], STDIN_FILENO) == -1)
        return (perror("dup2 failed"), -1);
    return (free(line), 1);
}

static int    heredoc(t_shell *shell, t_token *redir, int fd[3][2])
{
    int type;
    int i;
    char    *raw;

    i = (fd[2][0] + 1) % 2;
    close(fd[i][0]);
    close(fd[i][1]);
    if (pipe(fd[i]) == -1)
        return (perror("heredoc pipe failed"), -1);
    type = redir->quote_type;
    if (type == QUOTE_SINGLE || type == QUOTE_DOUBLE)
        type = QUOTE_SINGLE;
    raw = redir->value;
    redir->value = expand_str_hd(shell, raw, redir->quote_type);
    free(raw);
    if (!redir->value)
        return (perror("heredoc: expansion failed"), -1);
    return (here_doc_read(shell, redir->value, type, fd[i]));
}

int    here_doc(t_shell *shell, t_token *redir, int fd[3][2])
{
    int i;

    i = 0;
    while (redir)
    {
        if (redir->type == TOKEN_REDIRECT_HEREDOC)
            i = heredoc(shell, redir, fd);
        if (i == -1 || i == 2)
            break ;
        redir = redir->next;
    }
    if (i == -1)
        shell->exit_status = 1;
    if (i == 2)
        i = -1;
    return (i);
}
