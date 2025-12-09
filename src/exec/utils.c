

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

char    **get_path(char **paths, char *cmd)
{
    char    *full_path;
    char    **cmd_args;

    cmd_args = ft_split(cmd, ' ');
    while (*paths)
    {
        full_path = create_path(*paths, cmd_args[0]);
        if (access(full_path, X_OK) == 0)
            return (free(cmd_args[0]), cmd_args[0] = full_path, cmd_args);
        free(full_path);
        paths++;
    }
    return (NULL);
}

void    direct_io(t_command *cmd)
{
    int infile;
    int outfile;
    t_token *redir;

    redir = cmd->redirects;
    while (redir)
    {
        if (redir->type == TOKEN_REDIRECT_IN)
        {
            infile = open(redir->value, O_RDONLY);
            dup2(infile, STDIN_FILENO);
            close(infile);
        }
        else if (redir->type == TOKEN_REDIRECT_OUT)
        {
            outfile = open(redir->value, O_WRONLY | O_TRUNC | O_CREAT, 0644);
            dup2(outfile, STDOUT_FILENO);
            close(outfile);
        }
        redir = redir->next;
    }
}
