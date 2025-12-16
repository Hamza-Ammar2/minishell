

#include "../include/minishell.h"
#include "../libft/libft.h"


static void    rec_exec(char **paths, int fd[2][2], t_command *cmds, int i);
static int     check_cd(t_command *cmd);
static void    exec_single(t_command *cmd, char **paths);

static int     check_cd(t_command *cmd)
{
    char    *dir;

    if (!(cmd->args[0][0] == 'c' && cmd->args[0][1] == 'd'))
        return (0);
    dir = cmd->args[1];
    if (!dir)
        dir = getenv("HOME");
    if (chdir(dir) == -1)
        perror("chdir failed");
    if (!cmd->args[1])
        free(dir);
    return (1);
}

void    exec(t_command *cmds)
{
    int fd[2][2];
    char *path;
    char **paths;

    path = getenv("PATH");
    paths = ft_split(path, ':');
    rec_exec(paths, fd, cmds, 0);
    while(wait(NULL) > 0);
}

static void    exec_single(t_command *cmd, char **paths)
{
    char *str;

    direct_io(cmd);
    str = get_path(paths, cmd->args[0]);
    //envise(&cmd->args[1]);
    //printf("Executing: %s\n", str ? str : cmd->args[0]);
    execve(str, cmd->args, NULL);
    perror("execl failed");
    exit(1);
}

static void    connect_pipes(t_command *cmd, int fd[2][2], int i)
{
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

static void    rec_exec(char **paths, int fd[2][2], t_command *cmds, int i)
{
    int id;

    if (!cmds)
        return ;
    if (check_cd(cmds))
        return (rec_exec(paths, fd, cmds->next, i + 1));
    pipe(fd[i % 2]);
    id = fork();
    if (id == 0)
    {
        connect_pipes(cmds, fd, i);
        exec_single(cmds, paths);
    }
    if (i > 0)
    {
        close(fd[(i+1)%2][0]);
        close(fd[(i+1)%2][1]);
    }
    if (!cmds->next)
    {
        close(fd[i%2][0]);
        close(fd[i%2][1]);
        return ;
    }
    rec_exec(paths, fd, cmds->next, i + 1);
}
