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
	if (shell->cur_tokens)
		free_tokens(shell->cur_tokens);
	if (shell->input)
		free(shell->input);
	free_env(shell->env);
	get_next_line(-1);
	rl_clear_history();
}
