

#include "../include/minishell.h"
#include "../libft/libft.h"


char 	*do_env(t_shell *shell, char *str)
{
    //char    *s;
    t_env   *env;

    if (!str)
        return (NULL);
    // FIX: Handle edge case where $ is followed by invalid char or nothing
    if (!str[0] || (!ft_isalnum(str[0]) && str[0] != '_' && str[0] != '?'))
        return (ft_strdup("$"));
    if (str[0] == '?')
        return (ft_itoa(shell->exit_status));
    env = find_env(shell, str);
    if (env)
        return (free(str), ft_strdup(env->value));
    /* else
        s = getenv(str); */
    free(str);
    // FIX: Return empty string instead of NULL when variable not found
    // This matches bash behavior where undefined variables expand to empty string
    return (ft_strdup(""));
}

static char *join(char *s1, char *s2)
{
    char    *res;
    char    *tmp;

    if (!s2)
        return (s1);
    if (!s1)
        return (ft_strdup(s2));
    tmp = s1;
    res = ft_strjoin(s1, s2);
    free(tmp);
    return (res);
}

static char *find_end(char *str)
{
    if (*str == '?')
        return (str + 1);
    while (*str)
    {
        if (!ft_isalnum(*str) && *str != '_')
            return (str);
        str++;
    }
    return (NULL);
}

char    *expand_str(t_shell *shell, char *str, int quote_type)
{
    char    *start;
    char    *end;
    char    *res;

    if (!str || quote_type == QUOTE_SINGLE)
        return (ft_strdup(str));
    res = NULL;
    start = ft_strchr(str, '$');
    while (start)
    {
        end = find_end(start + 1);
        res = join(res, ft_substr(str, 0, start - str));
        if (end)
            res = join(res, do_env(shell, ft_substr(start + 1, 0, end - start - 1)));
        else
        {
            res = join(res, do_env(shell, ft_strdup(start + 1)));
            str = NULL;
            break ;
        }
        str = end;
        start = ft_strchr(str, '$');
    }
    return (res = join(res, str), res);
}
