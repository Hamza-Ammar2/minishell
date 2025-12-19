

#include "../include/minishell.h"
#include "../libft/libft.h"


static void    rec_exec(char **paths, int fd[3][2], t_command *cmds, t_shell *shell);
static int     check_builtin(t_command *cmds, t_shell *shell, int fd[3][2]);
static void    exec_single(t_command *cmd, t_shell *shell, char **paths);
static char    **wraper(t_token **args, t_shell *shell);
static void    connect_pipes(t_command *cmd, int fd[3][2]);

static void restore(int io[2])
{
    dup2(io[0], STDIN_FILENO);
    dup2(io[1], STDOUT_FILENO);
    close(io[0]);
    close(io[1]);
}

static int     check_builtin(t_command *cmds, t_shell *shell, int fd[3][2])
{
    char **args;
    int io[2];

    args = wraper(cmds->args, shell);
    io[0] = dup(STDIN_FILENO);
    io[1] = dup(STDOUT_FILENO);
    if (ft_strcmp(args[0], "pwd") == 0)
        return (connect_pipes(cmds, fd),
    direct_io(shell, cmds), pwd(), restore(io), 1);
    else if (ft_strcmp(args[0], "cd") == 0)
        return (connect_pipes(cmds, fd),
    direct_io(shell, cmds), cd(&args[1]), restore(io), 1);
    else if (ft_strcmp(args[0], "export") == 0)
        return (connect_pipes(cmds, fd),
        direct_io(shell, cmds), export(&args[1], shell), restore(io), 1);
    else if (ft_strcmp(args[0], "env") == 0)
        return (connect_pipes(cmds, fd),
        direct_io(shell, cmds), env(shell), restore(io), 1);
    else if (ft_strcmp(args[0], "echo") == 0)
        return (connect_pipes(cmds, fd),
            direct_io(shell, cmds), echo(&args[1]), restore(io), 1);
    else if (ft_strcmp(args[0], "unset") == 0)
        return (connect_pipes(cmds, fd),
            direct_io(shell, cmds), unset(shell, &args[1]), restore(io), 1);
    close(io[0]);
    close(io[1]);
    return (0);
}

void    exec(t_command *cmds, t_shell *shell)
{
    int fd[3][2];
    char *path;
    char **paths;

    fd[2][0] = 0;
    fd[2][1] = 1;
    path = getenv("PATH");
    paths = ft_split(path, ':');
    rec_exec(paths, fd, cmds, shell);
    while(wait(NULL) > 0);
}

static char **wraper(t_token **args, t_shell *shell)
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
        args_array[i] = expand_str(shell, args[i]->value, args[i]->quote_type);
        printf("ARG[%d]: %s\n", i, args_array[i]);
        i++;
    }
    args_array[count] = NULL;
    return (args_array);
}

static void    exec_single(t_command *cmd, t_shell *shell, char **paths)
{
    char *str;
    char **args;

    direct_io(shell, cmd);
    args = wraper(cmd->args, shell);
    str = get_path(paths, args[0]);
    execve(str, args, shell->envp);
    perror("execve failed");
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
        if (!fd[2][1])
            close(fd[(i+1)%2][1]);
    }
    else //if (!fd[2][1])
        close(fd[i%2][0]);
    if (cmd->next)
        dup2(fd[i%2][1], STDOUT_FILENO);
    else
        close(fd[i%2][0]);
    if (!fd[2][1])
        close(fd[i%2][0]);
    close(fd[i%2][1]);
}

static void    rec_exec(char **paths, int fd[3][2], t_command *cmds, t_shell *shell)
{
    if (!cmds)
        return ;
    pipe(fd[fd[2][0] % 2]);
    if (check_builtin(cmds, shell, fd))
        return (fd[2][0] = fd[2][0]+1, rec_exec(paths, fd, cmds->next, shell));
    fd[2][1] = fork();
    if (fd[2][1] == 0)
    {
        connect_pipes(cmds, fd);
        exec_single(cmds, shell, paths);
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
    (fd[2][0] = fd[2][0]+1, rec_exec(paths, fd, cmds->next, shell));
}
