/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_stuff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haammar <haammar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 03:02:08 by lpons             #+#    #+#             */
/*   Updated: 2026/02/07 09:25:44 by haammar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

t_env	*find_env(t_shell *shell, char *key)
{
	t_env	*current;

	if (!shell || !key)
		return (NULL);
	current = shell->env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

int	add_env(t_shell *shell, char *key, char *value)
{
	t_env	*new_env;
	t_env	*last;

	new_env = malloc(sizeof(t_env));
	if (!new_env)
	{
		perror("add_env: malloc failed");
		return (free(key), free(value), 0);
	}
	new_env->key = key;
	new_env->value = value;
	new_env->next = NULL;
	if (!shell->env)
	{
		shell->env = new_env;
		return (1);
	}
	last = shell->env;
	while (last->next)
		last = last->next;
	last->next = new_env;
	return (1);
}
