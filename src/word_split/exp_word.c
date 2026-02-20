/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpons <lpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 03:02:55 by lpons             #+#    #+#             */
/*   Updated: 2026/01/24 03:02:55 by lpons            ###   ########.fr       */
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

static char	*write_exp(char *res, t_shell *shell, char *str, int quote_type)
{
	char	*expanded;
	char	*raw;
	char	*tmp;
	int		i;

	i = get_next_quote(str + 1, quote_type) - str + 1;
	if (quote_type == QUOTE_NONE)
		i--;
	raw = ft_substr(str, 0, i);
	if (!raw)
		return (perror("could not expand string"), free(res), NULL);
	expanded = expand_quo(shell, raw, quote_type);
	if (!expanded)
		return (free(raw), free(res), perror("could not expand string"), NULL);
	tmp = res;
	res = ft_strjoin(res, expanded);
	if (!res)
		return (free(raw), free(tmp), free(expanded),
			perror("could not expand string"), NULL);
	free(expanded);
	free(raw);
	if (tmp)
		free(tmp);
	return (res);
}

char	*expand_word(t_shell *shell, char *str, int quote_type)
{
	char	*res;

	if (!str)
		return (NULL);
	res = ft_strdup("");
	if (!res)
		return (NULL);
	while (*str)
	{
		quote_type = quote2type(*str);
		res = write_exp(res, shell, str, quote_type);
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
