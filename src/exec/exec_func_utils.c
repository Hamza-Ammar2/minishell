

#include "../include/minishell.h"
#include "../libft/libft.h"

static int  pce(t_command *cmds, t_shell *shell, int fd[3][2], char **args)
{
    if (!(ft_strcmp(args[0], "pwd") == 0 ||
     ft_strcmp(args[0], "cd") == 0 || ft_strcmp(args[0], "export") == 0))
        return (0);
    if (connect_pipes(cmds, fd) == -1)
        return (-1);
    if (!direct_io(shell, cmds, fd))
        return (-1);
    if (ft_strcmp(args[0], "pwd") == 0)
        fd[2][1] = pwd(&args[1]);
    else if (ft_strcmp(args[0], "cd") == 0)
        fd[2][1] = cd(&args[1], shell);
    else
        fd[2][1] = export(&args[1], shell);
    return (1);
}

static int  eeu(t_command *cmds, t_shell *shell, int fd[3][2], char **args)
{
    if (!(ft_strcmp(args[0], "env") == 0 ||
     ft_strcmp(args[0], "echo") == 0 || ft_strcmp(args[0], "unset") == 0))
        return (0);
    if (connect_pipes(cmds, fd) == -1)
        return (-1);
    if (!direct_io(shell, cmds, fd))
        return (-1);
    if (ft_strcmp(args[0], "env") == 0)
        fd[2][1] = env(&args[1], shell);
    else if (ft_strcmp(args[0], "echo") == 0)
        fd[2][1] = echo(&args[1], shell);
    else
        fd[2][1] = unset(shell, &args[1]);
    return (1);
}

int     check_builtin(t_command *cmds, t_shell *shell, int fd[3][2])
{
    char **args;
    int i;

    args = wraper(cmds->args, shell);
    // FIX: If all tokens expanded to empty strings, args[0] will be NULL
    // In this case, there's no command to execute, just return success
    if (!args || !args[0])
        return (free_splits(args), 0);
    i = pce(cmds, shell, fd, args);
    if (i == -1 || i == 1)
        return (free_splits(args), i);
    i = eeu(cmds, shell, fd, args);
    if (i == -1 || i == 1)
        return (free_splits(args), i);
    free_splits(args);
    return (0);
}

void    free_splits(char **splits)
{
    int i;

    if (!splits)
        return ;
    i = 0;
    while (splits[i])
        free(splits[i++]);
    free(splits);
}

char **wraper(t_token **args, t_shell *shell)
{
    int     count;
    int     j;
    char    **args_array;
    char    *expanded;

    count = 0;
    while (args[count])
        count++;
    args_array = malloc(sizeof(char *) * (count + 1));
    if (!args_array)
        return (perror("could not create arguments list"), NULL);
    int i = 0;
    j = 0;
    // FIX: Skip empty expanded tokens (e.g., undefined variables) to match bash behavior
    while (i < count)
    {
        expanded = expand_str(shell, args[i]->value, args[i]->quote_type);
        if (!expanded)
            return (perror("could not create arguments list"), free_splits(args_array), NULL);
        // FIX: Only add non-empty strings to args_array (bash removes empty unquoted expansions)
        /* if (expanded[0] != '\0')
        { */
        args_array[j] = expanded;
        j++;
        /* }
        else
            free(expanded);  */// FIX: Free empty string since we're not adding it to array
        i++;
    }
    args_array[j] = NULL;
    return (args_array);
}
