/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haammar <haammar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 03:01:39 by lpons             #+#    #+#             */
/*   Updated: 2026/02/15 15:12:45 by haammar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

static void	del_one(t_shell *shell, char *arg)
{
	t_env	*current;
	t_env	*prev;
	t_env	*to_delete;

	current = shell->env;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, arg) == 0)
		{
			to_delete = current;
			if (prev)
				prev->next = current->next;
			else
				shell->env = current->next;
			free(to_delete->key);
			if (to_delete->value)
				free(to_delete->value);
			free(to_delete);
			break ;
		}
		prev = current;
		current = current->next;
	}
}

int	unset(t_shell *shell, char **args)
{
	while (*args)
	{
		del_one(shell, *args);
		args++;
	}
	return (0);
}
