

#include "../include/minishell.h"
#include "../libft/libft.h"

void    pwd()
{
    char    *cwd;

    cwd = getcwd(NULL, 0);
    if (!cwd)
        perror("getcwd failed");
    printf("%s\n", cwd);
    free(cwd);
}

/* void    export(char *str)
{
    (void *)(str);
} */


static char *do_env(char *str)
{
    char    *s;

    if (!str)
        return (NULL);
    s = getenv(str);
    free(str);
    return (s);
}

static char	*is_env(char *str)
{
    char    **splits;
    char    *s;
    char    *tmp;

    if (!ft_strchr(str, '$'))
        return (str);
    splits = ft_split(str, '$');
    s = splits[0];
    if (*str == '$')
        s = do_env(s);
    while (*(++splits))
    {
        tmp = s;
        *splits = do_env(*splits);
        s = ft_strjoin(*splits, tmp);
        free(tmp);
    }
    printf("%s", s);
    return (s);
}

char    **envise(char **args)
{
    char    **a;

    a = args;
    while (*args)
    {
        *args = is_env(*args);
        args++;
    }
    return (a);
}

