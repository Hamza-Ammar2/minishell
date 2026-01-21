

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
    // FIX: Handle edge case where $ is followed by invalid char or nothing
    // LEAK FIX: Free str before returning to prevent memory leak
    if (!str[0] || (!ft_isalnum(str[0]) && str[0] != '_' && str[0] != '?'))
        return (free(str), ft_strdup("$"));
    // LEAK FIX: Free str before returning exit status to prevent memory leak
    // This was a major leak source when $? was used in variable expansion
    if (str[0] == '?')
        return (free(str), ft_itoa(shell->exit_status));
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
    free(s1);  // Free the accumulated result string
    free(s2);  // LEAK FIX: Free the newly added string (from do_env/ft_substr)
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
        // LEAK FIX: Skip empty prefix to avoid allocating/freeing empty strings
        // This optimization prevents unnecessary allocation when $ is at start
        if (start - str > 0)
            res = join(res, ft_substr(str, 0, start - str));
        if (end)
            // All allocations here are freed by join() and do_env()
            res = join(res, do_env(shell, ft_substr(start + 1, 0, end - start - 1)));
        else
        {
            // Last variable expansion - no more text after this
            res = join(res, do_env(shell, ft_strdup(start + 1)));
            str = NULL;  // Mark str as consumed
            break ;
        }
        str = end;  // Move to remaining text after variable
        start = ft_strchr(str, '$');
    }
    // LEAK FIX: Handle remaining text after last variable expansion
    // Check str != NULL to avoid segfault from ft_strdup(NULL)
    // The duplicated string will be freed by join()
    if (str)
        res = join(res, ft_strdup(str));
    return (res);
}
