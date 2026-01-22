

#include "../include/minishell.h"
#include "../libft/libft.h"

static void del_one(t_shell *shell, char *arg)
{
    t_env   *current;
    t_env   *prev;
    t_env   *to_delete;

    current = shell->env;
    prev = NULL;
    while (current)
    {
        if (ft_strcmp(current->key, arg) == 0)
        {
            to_delete = current;
            if (prev)
                prev->next = current->next;
            else
                shell->env = current->next;
            free(to_delete->key);
            free(to_delete->value);
            free(to_delete);
            break ;
        }
        prev = current;
        current = current->next;
    }
}

int    unset(t_shell *shell, char **args)
{
    while (*args)
    {
        del_one(shell, *args);
        args++;
    }
    return (0);
}

static int exp_one(t_shell *shell, char *arg)
{
    char    *eq;
    char    *key;
    char    *value;
    t_env   *env;
    char    *plus_eq;

    // #PF Check for += operator (append) before regular =
    plus_eq = ft_strnstr(arg, "+=", ft_strlen(arg));
    if (plus_eq)
    {
        // #PF Handle VAR+=value (append to existing variable)
        key = ft_substr(arg, 0, plus_eq - arg);
        if (!key)
            return (perror("exp_one: malloc failed"), 0);
        value = ft_strdup(plus_eq + 2); // Skip the +=
        if (!value)
            return (free(key), perror("exp_one: malloc failed"), 0);
        env = find_env(shell, key);
        if (env && env->value)
        {
            // #PF Append to existing value
            char *new_value = ft_strjoin(env->value, value);
            if (!new_value)
                return (free(key), free(value), perror("exp_one: malloc failed"), 0);
            free(env->value);
            free(value);
            env->value = new_value;
            return (free(key), 1);
        }
        // #PF If variable doesn't exist, treat += as = (bash behavior)
        return (add_env(shell, key, value));
    }
    
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
    char    *plus_eq;

    if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
        return (0);
    
    // #PF Check for += operator - it's valid
    plus_eq = ft_strnstr(str, "+=", ft_strlen(str));
    if (plus_eq)
    {
        // #PF Validate the KEY part before +=
        char *key_part = str;
        while (key_part < plus_eq)
        {
            if (key_part == str && !ft_isalpha(*key_part) && *key_part != '_')
                return (0);
            if (key_part != str && !ft_isalnum(*key_part) && *key_part != '_')
                return (0);
            key_part++;
        }
        return (1); // #PF += is valid, value can be anything
    }
    
    str++;
    while (*str && *str != '=')
    {
        if (!ft_isalnum(*str) && *str != '_')
            return (0);
        str++;
    }
    // #PF Fix: Allow '=' in export VALUES, only validate the KEY part
    // Previous code rejected KEY=VALUE= (e.g., TES=T="")
    // Bash allows this: export TES=T="" sets TES to "T="
    // We've already validated the key, value can contain anything
    return (1);
}

int    export(char **args, t_shell *shell)
{
    int     exit_status;

    exit_status = 0; // FIX: Track if any errors occurred
    while (*args)
    {
        if (!isvalid_key(*args))
        {
            // FIX: Print to stderr (fd 2) not stdout, add newline, include the invalid arg
            fprintf(stderr, "export: `%s': not a valid identifier\n", *args);
            args++;
            exit_status = 1; // FIX: Mark that we had an error
            continue; // FIX: Continue processing other args but return error at end
        }
        if (!exp_one(shell, *args))
            return (1);
        args++;
    }
    return (exit_status); // FIX: Return 1 if any validation failed, 0 if all succeeded
}
