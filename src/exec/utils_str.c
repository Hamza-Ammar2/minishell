

#include "../include/minishell.h"
#include "../libft/libft.h"


// LEAK FIX: This function now properly frees the input 'str' parameter in ALL code paths.
// Previously, 'str' was only freed in some cases, causing leaks when expanding variables
// like $?, $INVALID_CHAR, or undefined variables.
char 	*do_env(t_shell *shell, char *str)
{
    //char    *s;
    t_env   *env;

    if (!str)
        return (NULL);
    if (!str[0] || (!ft_isalnum(str[0]) && str[0] != '_' && str[0] != '?'))
        return (free(str), ft_strdup("$"));
    if (str[0] == '?')
        return (free(str), ft_itoa(shell->exit_status));
    env = find_env(shell, str);
    if (env)
        return (free(str), ft_strdup(env->value));
    free(str);
    return (ft_strdup(""));
}

// LEAK FIX: This helper function now frees BOTH input strings after joining.
// Previously only freed s1, causing s2 to leak. This was a critical leak because
// expand_str calls join() with newly allocated strings from do_env() and ft_substr().
// Strategy: Since join creates a new combined string, both inputs are no longer needed.
static char *join(char *s1, char *s2)
{
    char    *res;

    if (!s2)
        return (s1);
    if (!s1)
        return (s2);
    res = ft_strjoin(s1, s2);
    free(s1);
    free(s2);
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

/* static char *get_start(char *str)
{
    while (*str)
    {
        if (ft_isalnum(*str) || *str == '_' || *str == '?')
            return (str);
        str++;
    }
    return (NULL);
} */

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
        if (start - str > 0)
            res = join(res, ft_substr(str, 0, start - str));
        if (end)
            res = join(res, do_env(shell, ft_substr(start + 1, 0, end - start - 1)));
        else
            return (join(res, do_env(shell, ft_strdup(start + 1))));
        str = end;
        start = ft_strchr(str, '$');
    }
    if (str)
        res = join(res, ft_strdup(str));
    return (res);
}
