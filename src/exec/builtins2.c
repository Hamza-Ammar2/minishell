

#include "../include/minishell.h"
#include "../libft/libft.h"

int exp_one(t_shell *shell, char *arg)
{
    char    *eq;
    char    *key;
    char    *value;
    t_env   *env;

    eq = ft_strchr(arg, '=');
    value = NULL;
    if (eq)
    {
        key = ft_substr(arg, 0, eq - arg);
        if (!key)
            return (perror("exp_one: malloc failed"), 0);
        value = ft_strdup(eq + 1);
        if (!value)
            return (free(key), perror("exp_one: malloc failed"), 0);
    }
    else
        key = ft_strdup(arg);
    if (!key)
        return (perror("exp_one: malloc failed"), 0);
    env = find_env(shell, key);
    if (env && eq)
        return (free(env->value),
        env->value = value, free(key), 1);
    return (add_env(shell, key, value));
}

static int  isvalid_key(char *str)
{
    if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
        return (0);
    str++;
    while (*str && *str != '=')
    {
        if (!ft_isalnum(*str) && *str != '_')
            return (0);
        str++;
    }
    /* if (!*str)
        return (1);
    else if (ft_strchr(str + 1, '='))
        return (0); */
    return (1);
}

void    bsort(char **args)
{
    int     i;
    int     swapped;
    char    *tmp;

    swapped = 1;
    while (swapped)
    {
        swapped = 0;
        i = 0;
        while (args[i + 1])
        {
            if (ft_strcmp(args[i], args[i + 1]) > 0)
            {
                tmp = args[i];
                args[i] = args[i + 1];
                args[i + 1] = tmp;
                swapped = 1;
            }
            i++;
        }
    }
}

static int print_export(t_shell *shell)
{
    char    **args;
    int     i;

    i = 0;
    args = env2arr(shell->env);
    if (!args)
        return (perror("print_export: malloc failed"), 1);
    bsort(args);
    while (args[i])
    {
        write(STDOUT_FILENO, "declare -x ", 11);
        write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
        write(STDOUT_FILENO, "\n", 1);
        i++;
    }
    return (free_splits(args), 0);
}

int    export(char **args, t_shell *shell)
{
    int     exit_status;

    if (!*args)
        return (print_export(shell));
    exit_status = 0;
    while (*args)
    {
        if (!isvalid_key(*args))
        {
            fprintf(stderr, "export: `%s': not a valid identifier\n", *args);
            args++;
            exit_status = 1;
            continue;
        }
        if (!exp_one(shell, *args))
            return (1);
        args++;
    }
    return (exit_status);
}
