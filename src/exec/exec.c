

#include "../include/minishell.h"
#include "../libft/libft.h"


static void    rec_exec(char **paths, int fd[2][2], t_command *cmds, int i);
static int     check_cd(t_token **cmd);
static void    exec_single(t_command *cmd, char **paths);
static char    **convert_args_to_argv(t_token **args);
static void    free_argv(char **argv);

/*
** Helper function to convert t_token** args to char** argv for execve
*/
static char    **convert_args_to_argv(t_token **args)
{
    char    **argv;
    int     i;
    int     count;

    count = 0;
    while (args[count])
        count++;
    argv = malloc(sizeof(char *) * (count + 1));
    if (!argv)
        return (NULL);
    i = 0;
    while (args[i])
    {
        argv[i] = args[i]->value;
        i++;
    }
    argv[i] = NULL;
    return (argv);
}

/*
** Helper function to free argv array (not values, just the array)
*/
static void    free_argv(char **argv)
{
    free(argv);
}

static int     check_cd(t_token **cmd)
{
    if (!cmd[0] || !cmd[0]->value)
        return (0);
    if (!(cmd[0]->value[0] == 'c' && cmd[0]->value[1] == 'd'))
        return (0);
    if (cmd[1] && cmd[1]->value)
        chdir(cmd[1]->value);
    perror("chdir failed");
    return (1);
}

void    exec(t_command *cmds, t_shell *shell)
{
    int fd[2][2];
    char *path;
    char **paths;
    int i;

    (void)shell;  // TODO: Use shell for environment and expansion
    path = getenv("PATH");
    paths = ft_split(path, ':');
    rec_exec(paths, fd, cmds, 0);
    while(wait(NULL) > 0);
    i = 0;
    while (paths[i])
        free(paths[i++]);
    free(paths);
}

static void    exec_single(t_command *cmd, char **paths)
{
    char **str;
    char **argv;

    direct_io(cmd);
    str = get_path(paths, cmd->args[0]->value);
    argv = convert_args_to_argv(cmd->args);
    execve(str[0], argv, NULL);
    perror("execl failed");
    free_argv(argv);
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
