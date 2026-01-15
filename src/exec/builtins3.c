

#include "../include/minishell.h"
#include "../libft/libft.h"

int    ft_exit(t_token **args, t_shell *shell)
{
    char *cmd;

    if (!args)
        return (-1);
    cmd = expand_str(shell, args[0]->value, args[0]->quote_type);
    if (ft_strcmp(cmd, "exit") != 0)
        return (free(cmd), -1);
    if (args && args[1])
    {
        fprintf(stderr, "exit: too many arguments\n");
        return (free(cmd), 1);
    }
    free(cmd);
    exit(shell->exit_status);
}
