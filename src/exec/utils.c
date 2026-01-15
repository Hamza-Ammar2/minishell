

#include "../include/minishell.h"
#include "../libft/libft.h"

char *create_path(char *path, char *cmd)
{
    char    *full_path;
    int     i;
    int     j;

    i = 0;
    full_path = malloc(strlen(path) + strlen(cmd) + 2);
    if (!full_path)
        return (perror("create_path: malloc failed"), NULL);
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

    if (access(full_path, F_OK) == 0)
        return (cmd);
    while (*paths)
    {
        full_path = create_path(*paths, cmd);
        if (!full_path)
            return (NULL);
        if (access(full_path, F_OK) == 0)
            return (full_path);
        free(full_path);
        paths++;
    }
    return (NULL);
}

int    restore(t_shell *shell)
{
    if (dup2(shell->stdin_backup, STDIN_FILENO) == -1)
        return (perror("restore: dup2 failed"), 1);
    if (dup2(shell->stdout_backup, STDOUT_FILENO) == -1)
        return (perror("restore: dup2 failed"), 1);
    return (0);
}
