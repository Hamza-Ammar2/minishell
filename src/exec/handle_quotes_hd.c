

#include "../include/minishell.h"
#include "../libft/libft.h"

static int quote2type(char c)
{
    if (c == '\'')
        return (QUOTE_SINGLE);
    if (c == '\"')
        return (QUOTE_DOUBLE);
    return (QUOTE_NONE);
}

static char    *get_next_quote(char *str, int quote_type)
{
    char    *q2;
    char    *q1;

    q1 = ft_strchr(str, '\'');
    q2 = ft_strchr(str, '\"');
    if (!q1)
        q1 = str + ft_strlen(str);
    if (!q2)
        q2 = str + ft_strlen(str);
    if (quote_type == QUOTE_SINGLE)
        return (q1);
    if (quote_type == QUOTE_DOUBLE)
        return (q2);
    if (q1 < q2)
        return (q1);
    return (q2);
}

static int write_exp(int fd[2], t_shell *shell, char *str, int quote_type)
{
    //char    *expanded;
    char    *raw;
    int     len;

    if (quote_type != QUOTE_NONE)
        str++;
    (void)shell;
    raw = ft_substr(str, 0, get_next_quote(str, quote_type) - str);
    if (!raw)
        return (perror("could not expand string"), -1);
    /* expanded = expand_quo(shell, raw, quote_type);
    if (!expanded)
        return (free(raw), perror("could not expand string"), -1); */
    len = ft_strlen(raw);
    write(fd[1], raw, len);
    free(raw);
    return (len);
}

static char    *get_buff(int fd[2], int total_len)
{
    char    *res;

    res = malloc(sizeof(char) * (total_len + 1));
    close(fd[1]);
    if (!res)
        return (close(fd[0]), perror("malloc failed"), NULL);
    if (read(fd[0], res, total_len) == -1)
        return (perror("read failed"), close(fd[0]), free(res), NULL);
    res[total_len] = '\0';
    close(fd[0]);
    return (res);
}

char    *expand_str_hd(t_shell *shell, char *str, int quote_type)
{
    int fd[2];
    int total_len;
    int len;

    if (!str)
        return (NULL);
    if (pipe(fd) == -1)
        return (perror("pipe failed"), NULL);
    total_len = 0;
    while (*str)
    {
        quote_type = quote2type(*str);
        len = write_exp(fd, shell, str, quote_type);
        if (len == -1)
            return (close(fd[0]), close(fd[1]), NULL);
        total_len += len;
        if (quote_type != QUOTE_NONE)
            str++;
        str = get_next_quote(str, quote_type);
        if (quote_type != QUOTE_NONE)
            str++;
    }
    return (get_buff(fd, total_len));
}
