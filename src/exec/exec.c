

#include "../include/minishell.h"
#include "../libft/libft.h"


static void    rec_exec(char **paths, int fd[2][2], t_command *cmds, t_shell *shell);
static int     check_cd(t_command *cmd);
static void    exec_single(t_command *cmd, char **paths);

static int     check_cd(t_command *cmd)
{
    char    *dir;

    if (!(cmd->args[0]->value[0] == 'c' && cmd->args[0]->value[1] == 'd'))
        return (0);
    dir = cmd->args[1]->value;
    if (!dir)
        dir = getenv("HOME");
    if (chdir(dir) == -1)
        perror("chdir failed");
    if (!cmd->args[1])
        free(dir);
    return (1);
}

void    exec(t_command *cmds, t_shell *shell)
{
    int fd[3][2];
    char *path;
    char **paths;

    fd[2][0] = 0;
    path = getenv("PATH");
    paths = ft_split(path, ':');
    rec_exec(paths, fd, cmds, shell);
    while(wait(NULL) > 0);
}

char **wraper(t_token **args)
{
    int     count;
    char    **args_array;

    count = 0;
    while (args[count])
        count++;
    args_array = malloc(sizeof(char *) * (count + 1));
    int i = 0;
    while (i < count)
    {
        args_array[i] = expand_str(args[i]->value, args[i]->quote_type);
        printf("ARG[%d]: %s\n", i, args_array[i]);
        i++;
    }
    args_array[count] = NULL;
    return (args_array);
}

static void    exec_single(t_command *cmd, char **paths)
{
    char *str;

    direct_io(cmd);
    str = get_path(paths, cmd->args[0]->value);
    execve(str, wraper(cmd->args), NULL);
    perror("execl failed");
    exit(1);
}

static void    connect_pipes(t_command *cmd, int fd[3][2])
{
    int i;

    i = fd[2][0];
    if (i > 0)
    {
        dup2(fd[(i+1)%2][0], STDIN_FILENO);
        close(fd[(i+1)%2][0]);
        close(fd[(i+1)%2][1]);
    }
    if (cmd->next)
        dup2(fd[i%2][1], STDOUT_FILENO);
    close(fd[i%2][0]);
    close(fd[i%2][1]);
}

static void    rec_exec(char **paths, int fd[2][2], t_command *cmds, t_shell *shell)
{
    int id;

    if (!cmds)
        return ;
    if (check_cd(cmds))
        return (fd[2][0] = !fd[2][0], rec_exec(paths, fd, cmds->next, shell));
    pipe(fd[fd[2][0] % 2]);
    id = fork();
    if (id == 0)
    {
        connect_pipes(cmds, fd);
        exec_single(cmds, paths);
    }
    if (fd[2][0] > 0)
    {
        close(fd[(fd[2][0]+1)%2][0]);
        close(fd[(fd[2][0]+1)%2][1]);
    }
    if (!cmds->next)
    {
        close(fd[fd[2][0]%2][0]);
        close(fd[fd[2][0]%2][1]);
        return ;
    }
    (fd[2][0] = !fd[2][0], rec_exec(paths, fd, cmds->next, shell));
}
