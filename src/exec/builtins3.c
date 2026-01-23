

#include "../include/minishell.h"
#include "../libft/libft.h"


static int is_numeric(char *str)
{
    int i;

    i = 0;
    if (str[i] == '+' || str[i] == '-')
        i++;
    if (!str[i])
        return (0);
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }
    return (1);
}

int    ft_exit(t_token **args, t_shell *shell)
{
    char *cmd;
    char *exit_arg;
    int exit_code;

    if (!args)
        return (-1);
    cmd = expand_str(shell, args[0]->value, args[0]->quote_type);
    if (ft_strcmp(cmd, "exit") != 0)
        return (free(cmd), -1);
    free(cmd);
    if (args[1])
    {
        exit_arg = expand_str(shell, args[1]->value, args[1]->quote_type);
        if (!is_numeric(exit_arg))
        {
            fprintf(stderr, "exit: %s: numeric argument required\n", exit_arg);
            free(exit_arg);
            shell->exit_status = 2;
            exit(2);
        }
        if (args[2])
        {
            fprintf(stderr, "exit: too many arguments\n");
            free(exit_arg);
            shell->exit_status = 1;
            return (1);
        }
        exit_code = ft_atoi(exit_arg);
        free(exit_arg);
        shell->exit_status = (unsigned char)exit_code;
        exit((unsigned char)exit_code);
    }
    exit(shell->exit_status);
}
