/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haammar <haammar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 02:47:05 by lpons             #+#    #+#             */
/*   Updated: 2026/02/18 01:06:05 by haammar          ###   ########.fr       */
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
	/* LEAK FIX: Free current tokens if exit was called mid-execution.
	** Previously tokens allocated in process_input were never freed
	** when exit_nice was called, causing ~37 bytes leak per exit. */
	if (shell->cur_tokens)
		free_tokens(shell->cur_tokens);
	/* EXTRA LEAK FIX: Free input line if exit was called mid-execution.
	** May revert if this leak turns out to be from readline, not our code. */
	if (shell->input)
		free(shell->input);
	free_env(shell->env);
	/* LEAK FIX: Free get_next_line static buffer by calling with fd=-1.
	** Previously the static buffer was never freed, causing ~16 bytes leak. */
	get_next_line(-1);
	rl_clear_history();
}
