

#include "../include/minishell.h"
#include "../libft/libft.h"


static int    rec_exec(char **paths, int fd[3][2], t_command *cmds, t_shell *shell);
static void    exec_single(t_command *cmd, t_shell *shell, char **paths);

void    exec(t_command *cmds, t_shell *shell)
{
    int fd[3][2];
    char *path;
    char **paths;

    fd[2][0] = 0;
    fd[2][1] = 1;
    path = getenv("PATH");
    paths = ft_split(path, ':');
    shell->exit_status = rec_exec(paths, fd, cmds, shell);
    while(wait(NULL) > 0);
    free_splits(paths);
}

static void    exec_single(t_command *cmd, t_shell *shell, char **paths)
{
    char *str;
    char **args;

    args = wraper(cmd->args, shell);
    if (!args)
        exit(1);
    str = get_path(paths, args[0]);
    if (!direct_io(shell, cmd))
        exit(1);
    execve(str, args, shell->envp);
    perror("execve failed");
    exit(1);
}

int    connect_pipes(t_command *cmd, int fd[3][2])
{
    int i;
    int failed;

    i = fd[2][0];
    failed = 0;
    if (i > 0)
    {
        failed = dup2(fd[(i+1)%2][0], STDIN_FILENO);
        close(fd[(i+1)%2][0]);
        if (!fd[2][1])
            close(fd[(i+1)%2][1]);
    }
    else //if (!fd[2][1])
        close(fd[i%2][0]);
    if (cmd->next)
        failed = dup2(fd[i%2][1], STDOUT_FILENO);
    else
        close(fd[i%2][0]);
    if (!fd[2][1])
        close(fd[i%2][0]);
    close(fd[i%2][1]);
    if (failed == -1)
        perror("dup2: connecting pipes failed");
    return (failed);
}

static int  close_pipes(t_command *cmds, int fd[3][2])
{
    if (fd[2][1] < 0)
    {
        if (fd[2][0] > 0)
        {
            close(fd[(fd[2][0]+1)%2][0]);
            close(fd[(fd[2][0]+1)%2][1]);
        }
        return (1);
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
        return (1);
    }
    return (0);
} 

static int    rec_exec(char **paths, int fd[3][2], t_command *cmds, t_shell *shell)
{
    int cb;

    if (!cmds)
        return (0);
    if (pipe(fd[fd[2][0] % 2]) != 0)
        return (fd[2][1] = -1, close_pipes(cmds, fd), perror("pipe failed"), 1);
    cb = check_builtin(cmds, shell, fd);
    if (cb == 1)
        return (fd[2][0] = fd[2][0] + 1, rec_exec(paths, fd, cmds->next, shell));
    else if (cb == -1)
        return (close_pipes(cmds, fd), 1);
    fd[2][1] = fork();
    if (fd[2][1] < 0)
        return (close_pipes(cmds, fd), perror("fork failed"), 1);
    if (fd[2][1] == 0)
    {
        if (connect_pipes(cmds, fd) != -1)
            exec_single(cmds, shell, paths);
        exit(1);
    }
    if (close_pipes(cmds, fd))
        return (0);
    return (fd[2][0] = fd[2][0] + 1, rec_exec(paths, fd, cmds->next, shell));
}
