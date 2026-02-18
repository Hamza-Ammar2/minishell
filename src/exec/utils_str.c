/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haammar <haammar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 03:03:33 by lpons             #+#    #+#             */
/*   Updated: 2026/02/18 03:51:24 by haammar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

char	*do_env(t_shell *shell, char *str)
{
	t_env	*env;

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

static char	*join(char *s1, char *s2)
{
	char	*res;

	if (!s2)
		return (s1);
	if (!s1)
		return (s2);
	res = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (res);
}

static char	*find_end(char *str)
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

void	free_splits(char **splits)
{
	int	i;

	if (!splits)
		return ;
	i = 0;
	while (splits[i])
		free(splits[i++]);
	free(splits);
}

char	*expand_quo(t_shell *shell, char *str, int quote_type)
{
	char	*start;
	char	*end;
	char	*res;

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
			res = join(res, do_env(shell, ft_substr(start + 1, 0, end - start
							- 1)));
		else
			return (join(res, do_env(shell, ft_strdup(start + 1))));
		str = end;
		start = ft_strchr(str, '$');
	}
	if (str)
		res = join(res, ft_strdup(str));
	return (res);
}
