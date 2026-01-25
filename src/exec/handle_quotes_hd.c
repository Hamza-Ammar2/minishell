/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes_hd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haammar <haammar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 03:03:03 by lpons             #+#    #+#             */
/*   Updated: 2026/01/25 01:57:58 by haammar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

static int	quote2type(char c)
{
	if (c == '\'')
		return (QUOTE_SINGLE);
	if (c == '\"')
		return (QUOTE_DOUBLE);
	return (QUOTE_NONE);
}

static char	*get_next_quote(char *str, int quote_type)
{
	char	*q2;
	char	*q1;

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

static char	*write_exp(char *res, char *str, int quote_type)
{
	char	*raw;
	char	*tmp;

	if (quote_type != QUOTE_NONE)
		str++;
	raw = ft_substr(str, 0, get_next_quote(str, quote_type) - str);
	if (!raw)
		return (perror("could not expand string"), NULL);
	tmp = res;
	res = ft_strjoin(res, raw);
	if (!res)
		return (free(raw), perror("could not expand string"), NULL);
	free(raw);
	if (tmp)
		free(tmp);
	return (res);
}

/* static char	*get_buff(int fd[2], int total_len)
{
	char	*res;

	res = malloc(sizeof(char) * (total_len + 1));
	close(fd[1]);
	if (!res)
		return (close(fd[0]), perror("malloc failed"), NULL);
	if (read(fd[0], res, total_len) == -1)
		return (perror("read failed"), close(fd[0]), free(res), NULL);
	res[total_len] = '\0';
	close(fd[0]);
	return (res);
} */

char	*expand_str_hd(t_shell *shell, char *str, int quote_type)
{
	char	*res;

	if (!str)
		return (NULL);
	res = ft_strdup("");
	(void)shell;
	if (!res)
		return (NULL);
	while (*str)
	{
		quote_type = quote2type(*str);
		res = write_exp(res, str, quote_type);
		if (!res)
			return (NULL);
		if (quote_type != QUOTE_NONE)
			str++;
		str = get_next_quote(str, quote_type);
		if (quote_type != QUOTE_NONE)
			str++;
	}
	return (res);
}
