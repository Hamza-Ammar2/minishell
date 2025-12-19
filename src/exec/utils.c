

#include "../include/minishell.h"
#include "../libft/libft.h"

char *create_path(char *path, char *cmd)
{
    char    *full_path;
    int     i;
    int     j;

    i = 0;
    full_path = malloc(strlen(path) + strlen(cmd) + 2);
    while (path[i])
    {
        full_path[i] = path[i];
        i++;
    }
    full_path[i] = '/';
    i++;
    j = 0;
    while (cmd[j])
    {
        full_path[i + j] = cmd[j];
        j++;
    }
    return (full_path[i + j] = '\0', full_path);
}

char    *get_path(char **paths, char *cmd)
{
    char    *full_path;

    while (*paths)
    {
        full_path = create_path(*paths, cmd);
        if (access(full_path, X_OK) == 0)
            return (full_path);
        free(full_path);
        paths++;
    }
    return (cmd);
}

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

static void    here_doc_app(t_shell *shell, t_token *redir)
{
    int file;
    char *line;
    int fd[2];

    if (redir->type == TOKEN_REDIRECT_APPEND)
    {
        file = open(redir->value, O_WRONLY | O_APPEND | O_CREAT, 0644);
        dup2(file, STDOUT_FILENO);
        close(file);
    }
    else if (redir->type == TOKEN_REDIRECT_HEREDOC)
    {
        pipe(fd);
        line = expand_str(shell, readline("> "), redir->quote_type);
        while (strcmpy(line, redir->value) != 0)
        {
            write(fd[1], line, strlen(line));
            write(fd[1], "\n", 1);
            free(line);
            line = expand_str(shell, readline("> "), redir->quote_type);
            if (!line)
                break ;
        }
        dup2(fd[0], STDIN_FILENO);
        close(fd[1]);
        close(fd[0]);
        free(line);
    }
}

void    direct_io(t_shell *shell, t_command *cmd)
{
    int file;
    t_token *redir;

    redir = cmd->redirects;
    while (redir)
    {
        if (redir->type == TOKEN_REDIRECT_IN)
        {
            file = open(redir->value, O_RDONLY);
            dup2(file, STDIN_FILENO);
            close(file);
        }
        else if (redir->type == TOKEN_REDIRECT_OUT)
        {
            file = open(redir->value, O_WRONLY | O_TRUNC | O_CREAT, 0644);
            printf("Redirecting output to %s\n", redir->value);
            dup2(file, STDOUT_FILENO);
            close(file);
        }
        else
            here_doc_app(shell, redir);
        redir = redir->next;
    }
}
