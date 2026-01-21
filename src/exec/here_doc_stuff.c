
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

static int  here_doc_read(t_shell *shell, char *value, int type, int fd[2])
{
    char *line;
    char *raw_line;

    // FIX: In non-interactive mode, heredocs can't work properly because stdin is shared
    // between main loop and heredoc reading. Skip heredoc and create empty pipe.
    if (!isatty(STDIN_FILENO))
    {
        close(fd[1]);
        if (dup2(fd[0], STDIN_FILENO) == -1)
            return (perror("dup2 failed"), close(fd[0]), -1);
        return (1);
    }

    raw_line = readline("> ");
    line = expand_str(shell, raw_line, type);
    if (sig)
        return (clean_stuff(shell, fd, line));
    while (strcmpy(line, value) != 0)
    {
        write(fd[1], line, ft_strlen(line));
        write(fd[1], "\n", 1);
        free(line);
        raw_line = readline("> ");
        line = expand_str(shell, raw_line, type);
        if (sig)
            return (clean_stuff(shell, fd, line));
        if (!line)
            break ;
    }
    //close(fd[1]);
    if (dup2(fd[0], STDIN_FILENO) == -1)
        return (perror("dup2 failed222"), -1);
    return (free(line), 1);
}

static int    heredoc(t_shell *shell, t_token *redir, int fd[3][2])
{
    int type;
    int i;

    i = (fd[2][0] + 1) % 2;
    close(fd[i][0]);
    close(fd[i][1]);
    if (pipe(fd[i]) == -1)
        return (perror("heredoc pipe failed"), -1);
    type = redir->quote_type;
    if (type == QUOTE_SINGLE || type == QUOTE_DOUBLE)
        type = QUOTE_SINGLE;
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
