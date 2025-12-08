

#include "../include/minishell.h"

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

void exec(int argc, char **argv)
{
    int n_args = argc - 1;
    int fd[2][2];
    int id;
    int infile = open(argv[1], O_RDONLY);
    int outfile = open(argv[argc - 1], O_WRONLY | O_TRUNC);
    char *pathy = getenv("PATH"); 
    char **paths = ft_split(pathy, ':');

    for (int i = 0; i < n_args; i ++)
    {   
        pipe(fd[i % 2]);
        id = fork();
        if (id == 0)
        {
            if (i > 0)
            {
                dup2(fd[(i+1)%2][0], STDIN_FILENO);
                close(fd[(i+1)%2][0]);
                close(fd[(i+1)%2][1]);
            }
            /* else
                dup2(infile, STDIN_FILENO); */
            if (i < n_args - 1)
            {
                dup2(fd[i%2][1], STDOUT_FILENO);
                close(fd[i%2][0]);
                close(fd[i%2][1]);
            }
            /* else
                dup2(outfile, STDOUT_FILENO); */
            char    **str = get_path(paths, argv[i + 1]);
            execve(str[0], str, NULL);
            perror("execl failed");
            exit(1);
        }
        if (i > 0)
        {
            close(fd[(i+1)%2][0]);
            close(fd[(i+1)%2][1]);
        }
    }
    close(infile);
    close(outfile);
    while (wait(NULL) > 0);
    return (0);
}
