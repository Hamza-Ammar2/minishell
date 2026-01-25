/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpons <lpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 02:47:05 by lpons             #+#    #+#             */
/*   Updated: 2026/01/25 00:47:35 by lpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

/*
** 🔧 What the function Does
** Frees all allocated resources and cleans up the shell.
**
** 🔗 Role in the Program
** Ensures proper memory cleanup before program termination.
**
** 🧩 Step-by-Step
** 1. Clear readline history.
*/

void	free_env(t_env *env)
{
	t_env	*current;
	t_env	*next;

	current = env;
	while (current)
	{
		next = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next;
	}
}

void	cleanup_shell(t_shell *shell)
{
	restore(shell);
	close(shell->stdin_backup);
	close(shell->stdout_backup);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	free_env(shell->env);
	rl_clear_history();
}
