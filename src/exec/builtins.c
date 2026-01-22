

#include "../include/minishell.h"
#include "../libft/libft.h"

int    pwd(char **args)
{
    char    *cwd;

    // FIX: pwd should accept no arguments, not check if args exist
    // args is passed as &args[1] from caller, so args[0] is the first actual argument
    // We want to allow pwd with no args, reject pwd with args
    (void)args; // pwd doesn't take arguments in our implementation
    cwd = getcwd(NULL, 0);
    if (!cwd)
        return (perror("getcwd failed\n"), 1);
    // FIX: Use write() instead of printf() to avoid buffering issues that cause output order problems
    write(STDOUT_FILENO, cwd, ft_strlen(cwd));
    write(STDOUT_FILENO, "\n", 1);
    free(cwd);
    return (0);
}

int    env(char **args, t_shell *shell)
{
    t_env   *current;

    if (args && args[0])
    {
        fprintf(stderr, "env: too many arguments\n");
        return (1);
    }
    current = shell->env;
    // FIX: Use write() instead of printf() to avoid buffering issues that cause output order problems
    while (current)
    {
        if (current->value)
        {
            write(STDOUT_FILENO, current->key, ft_strlen(current->key));
            write(STDOUT_FILENO, "=", 1);
            write(STDOUT_FILENO, current->value, ft_strlen(current->value));
            write(STDOUT_FILENO, "\n", 1);
        }
        current = current->next;
    }
    return (0);
}

int    echo(char **args)
{
    int     newline;
    int     i;

    newline = 1;
    i = 0;
    while (args[i] && ft_strcmp(args[i], "-n") == 0)
    {
        newline = 0;
        i++;
    }
    while (args[i])
    {
        write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
        if (args[i + 1] /* && *args[i] */)
            write(STDOUT_FILENO, " ", 1);
        i++;
    }
    if (newline)
        write(STDOUT_FILENO, "\n", 1);
    return (0);
}
