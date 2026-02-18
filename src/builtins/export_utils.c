/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haammar <haammar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 08:52:43 by haammar           #+#    #+#             */
/*   Updated: 2026/02/17 20:57:06 by haammar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

int	exp_one_peq(t_shell *shell, char *arg, char *peq)
{
	char	*key;
	char	*value;
	char	*tmp;
	t_env	*env;

	value = NULL;
	key = ft_substr(arg, 0, peq - arg);
	if (!key)
		return (perror("exp_one: malloc failed"), 0);
	value = ft_strdup(peq + 2);
	if (!value)
		return (free(key), perror("exp_one: malloc failed"), 0);
	env = find_env(shell, key);
	if (env)
	{
		tmp = ft_strjoin(env->value, value);
		if (!tmp)
			return (free(key), free(value), perror("exp_one: malloc failed"),
				0);
		return (free(env->value), free(value), env->value = tmp, free(key), 1);
	}
	return (add_env(shell, key, value));
}

static void	handle_exists(t_env *env, char *key, char *value)
{
	free(key);
	if (value)
	{
		free(env->value);
		env->value = value;
	}
}

int	exp_one(t_shell *shell, char *arg)
{
	char	*eq;
	char	*key;
	char	*value;
	t_env	*env;

	eq = ft_strchr(arg, '=');
	value = NULL;
	if (eq)
	{
		key = ft_substr(arg, 0, eq - arg);
		if (!key)
			return (perror("exp_one: malloc failed"), 0);
		value = ft_strdup(eq + 1);
		if (!value)
			return (free(key), perror("exp_one: malloc failed"), 0);
	}
	else
		key = ft_strdup(arg);
	if (!key)
		return (perror("exp_one: malloc failed"), 0);
	env = find_env(shell, key);
	if (env)
		return (handle_exists(env, key, value), 1);
	return (add_env(shell, key, value));
}
