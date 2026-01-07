

#include "../include/minishell.h"
#include "../libft/libft.h"

t_env    *find_env(t_shell *shell, char *key)
{
    t_env   *current;

    if (!shell || !key)
        return (NULL);
    current = shell->env;
    while (current)
    {
        if (ft_strcmp(current->key, key) == 0)
            return (current);
        current = current->next;
    }
    return (NULL);
}

int    add_env(t_shell *shell, char *key, char *value)
{
    t_env   *new_env;
    t_env   *last;

    new_env = malloc(sizeof(t_env));
    if (!new_env)
    {
        perror("add_env: malloc failed");
        return (0);
    }
    new_env->key = key;
    new_env->value = value;
    new_env->next = NULL;
    if (!shell->env)
    {
        shell->env = new_env;
        return (1);
    }
    last = shell->env;
    while (last->next)
        last = last->next;
    last->next = new_env;
    return (1);
}
