

#include "../include/minishell.h"
#include "../libft/libft.h"


static void    rec_exec(char **paths, int fd[2][2], t_command *cmds, int i);
static int     check_cd(char **cmd);
static void    exec_single(t_command *cmd, char **paths);

static int     check_cd(char **cmd)
{
    if (!(cmd[0][0] == 'c' && cmd[0][1] == 'd'))
        return (0);
    chdir(cmd[1]);
    perror("chdir failed");
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
    char **str;

    direct_io(cmd);
    str = get_path(paths, cmd->args[0]);
    execve(str[0], cmd->args, NULL);
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

    if (check_cd(cmds->args))
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
