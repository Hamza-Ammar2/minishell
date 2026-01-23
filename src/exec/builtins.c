

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

static  int is_n_flag(char *arg)
{
    int i;

    if (!arg || arg[0] != '-')
        return (0);
    i = 1;
    while (arg[i])
    {
        if (arg[i] != 'n')
            return (0);
        i++;
    }
    if (i == 1)
        return (0);
    return (1);
}

static  int    write_tilde(char *arg, t_shell *shell)
{
    t_env   *home;

    if (arg[0] == '~' && (arg[1] == '/' || arg[1] == '\0'))
    {
        home = find_env(shell, "HOME");
        if (!home)
            return (write(STDOUT_FILENO, arg, ft_strlen(arg)));
        write(STDOUT_FILENO, home->value, ft_strlen(home->value));
        write(STDOUT_FILENO, arg + 1, ft_strlen(arg + 1));
        return (1);
    }
    return (write(STDOUT_FILENO, arg, ft_strlen(arg)));
}

int    echo(char **args, t_shell *shell)
{
    int     newline;
    int     i;

    newline = 1;
    i = 0;
    while (args[i] && is_n_flag(args[i]))
    {
        newline = 0;
        i++;
    }
    while (args[i])
    {
        write_tilde(args[i], shell);
        if (args[i + 1] /* && *args[i] */)
            write(STDOUT_FILENO, " ", 1);
        i++;
    }
    if (newline)
        write(STDOUT_FILENO, "\n", 1);
    return (0);
}
