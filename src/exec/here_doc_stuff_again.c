

#include "../include/minishell.h"
#include "../libft/libft.h"

char    *make_hd()
{
    static int name;
    char    *tmp;
    char    *file;

    tmp = ft_itoa(name);
    if (!tmp)
        return (NULL);
    file = ft_strjoin("/tmp/", tmp);
    if (!file)
        return (free(tmp), NULL);
    free(tmp);
    while (access(file, F_OK) != -1)
    {
        name++;
        tmp = ft_itoa(name);
        if (!tmp)
            return (NULL);
        free(file);
        file = ft_strjoin("/tmp/", tmp);
        if (!file)
            return (NULL);
        free(tmp);
    }
    return (file);
}
