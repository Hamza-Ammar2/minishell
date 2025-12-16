

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
    return (NULL);
}

void    direct_io(t_command *cmd)
{
    int infile;
    int outfile;
    t_token *redir;

    redir = cmd->redirects;
    printf("Setting up I/O redirections for command: %s\n", redir ? redir->value : "none");
    while (redir)
    {
        printf("Processing redirection: %s %s\n",
            (redir->type == TOKEN_REDIRECT_IN) ? "<" : ">",
            redir->value);
        if (redir->type == TOKEN_REDIRECT_IN)
        {
            infile = open(redir->value, O_RDONLY);
            dup2(infile, STDIN_FILENO);
            close(infile);
        }
        else if (redir->type == TOKEN_REDIRECT_OUT)
        {
            printf("Redirecting output to %s\n", redir->value);
            outfile = open(redir->value, O_WRONLY | O_TRUNC | O_CREAT, 0644);
            dup2(outfile, STDOUT_FILENO);
            close(outfile);
        }
        redir = redir->next;
    }
}
