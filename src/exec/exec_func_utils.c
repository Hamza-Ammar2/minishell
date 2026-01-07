

#include "../include/minishell.h"
#include "../libft/libft.h"

static int  pce(t_command *cmds, t_shell *shell, int fd[3][2], char **args)
{
    if (!(ft_strcmp(args[0], "pwd") == 0 ||
     ft_strcmp(args[0], "cd") == 0 || ft_strcmp(args[0], "export") == 0))
        return (0);
    if (connect_pipes(cmds, fd) == -1)
        return (-1);
    if (!direct_io(shell, cmds))
        return (-1);
    if (ft_strcmp(args[0], "pwd") == 0)
        pwd();
    else if (ft_strcmp(args[0], "cd") == 0)
        cd(&args[1]);
    else
        export(&args[1], shell);
    if (dup2(shell->stdin_backup, STDIN_FILENO) == -1)
        return (perror("built_in: dup2 failed"), -1);
    if (dup2(shell->stdout_backup, STDOUT_FILENO) == -1)
        return (perror("built_in: dup2 failed"), -1);
    return (1);
}

static int  eeu(t_command *cmds, t_shell *shell, int fd[3][2], char **args)
{
    if (!(ft_strcmp(args[0], "env") == 0 ||
     ft_strcmp(args[0], "echo") == 0 || ft_strcmp(args[0], "unset") == 0))
        return (0);
    if (connect_pipes(cmds, fd) == -1)
        return (-1);
    if (!direct_io(shell, cmds))
        return (-1);
    if (ft_strcmp(args[0], "env") == 0)
        env(shell);
    else if (ft_strcmp(args[0], "echo") == 0)
        echo(&args[1]);
    else
        unset(shell, &args[1]);
    if (dup2(shell->stdin_backup, STDIN_FILENO) == -1)
        return (perror("built_in: dup2 failed"), -1);
    if (dup2(shell->stdout_backup, STDOUT_FILENO) == -1)
        return (perror("built_in: dup2 failed"), -1);
    return (1);
}

int     check_builtin(t_command *cmds, t_shell *shell, int fd[3][2])
{
    char **args;
    int i;

    args = wraper(cmds->args, shell);
    i = pce(cmds, shell, fd, args);
    if (i == -1 || i == 1)
        return (i);
    i = eeu(cmds, shell, fd, args);
    if (i == -1 || i == 1)
        return (i);
    return (0);
}

void    free_splits(char **splits)
{
    int i = 0;
    while (splits[i])
        free(splits[i++]);
    free(splits);
}

char **wraper(t_token **args, t_shell *shell)
{
    int     count;
    char    **args_array;

    count = 0;
    while (args[count])
        count++;
    args_array = malloc(sizeof(char *) * (count + 1));
    if (!args_array)
        return (perror("could not create arguments list"), NULL);
    int i = 0;
    while (i < count)
    {
        args_array[i] = expand_str(shell, args[i]->value, args[i]->quote_type);
        if (!args_array[i])
            return (perror("could not create arguments list"), free_splits(args_array), NULL);
        //printf("ARG[%d]: %s\n", i, args_array[i]);
        i++;
    }
    args_array[count] = NULL;
    return (args_array);
}
