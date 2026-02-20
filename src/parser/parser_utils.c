/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpons <lpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 03:04:59 by lpons             #+#    #+#             */
/*   Updated: 2026/01/24 03:05:47 by lpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_command	*new_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->redirects = NULL;
	cmd->next = NULL;
	return (cmd);
}

void	free_commands(t_command *commands)
{
	t_command	*next;
	int			i;

	while (commands)
	{
		next = commands->next;
		if (commands->args)
		{
			i = 0;
			while (commands->args[i])
			{
				free_tokens(commands->args[i]);
				i++;
			}
			free(commands->args);
		}
		free_tokens(commands->redirects);
		free(commands);
		commands = next;
	}
}

t_token	*get_last_token(t_token *tokens)
{
	if (!tokens)
		return (NULL);
	while (tokens->next)
		tokens = tokens->next;
	return (tokens);
}

/* LEAK FIX: Set start pointer for all commands in pipeline.
** This allows exit_nice to free entire list from any cmd. */
void	set_pipeline_start(t_command *head)
{
	t_command	*current;

	current = head;
	while (current)
	{
		current->start = head;
		current = current->next;
	}
}
