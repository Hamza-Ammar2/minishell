/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpons <lpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 03:05:06 by lpons             #+#    #+#             */
/*   Updated: 2026/01/25 14:55:30 by lpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_args(t_token *tokens)
{
	int		count;
	t_token	*current;

	count = 0;
	current = tokens;
	while (current && current->type != TOKEN_PIPE)
	{
		if (current->type == TOKEN_WORD)
			count++;
		else if (is_redirect_type(current->type))
		{
			if (current->next)
				current = current->next;
		}
		current = current->next;
	}
	return (count);
}

static int	fill_args(t_command *cmd, t_token *tokens)
{
	int		i;
	t_token	*current;

	i = 0;
	current = tokens;
	while (current)
	{
		if (current->type == TOKEN_WORD)
		{
			cmd->args[i] = new_token(TOKEN_WORD, current->value,
					current->quote_type);
			if (!cmd->args[i])
				return (-1);
			i++;
		}
		else if (is_operator_token(current->type))
		{
			if (current->next)
				current = current->next;
		}
		current = current->next;
	}
	cmd->args[i] = NULL;
	return (0);
}

static t_command	*parse_single_command(t_token *tokens)
{
	t_command	*cmd;
	int			arg_count;

	cmd = new_command();
	if (!cmd)
		return (NULL);
	parse_redirections(cmd, tokens);
	arg_count = count_args(tokens);
	cmd->args = malloc(sizeof(t_token *) * (arg_count + 1));
	if (!cmd->args)
	{
		free_commands(cmd);
		return (NULL);
	}
	if (fill_args(cmd, tokens) == -1)
	{
		free_commands(cmd);
		return (NULL);
	}
	return (cmd);
}

t_command	*parse(t_token *tokens)
{
	t_command	*cmd;

	if (!tokens)
		return (NULL);
	if (count_pipes(tokens) > 0)
		return (parse_pipeline(tokens));
	cmd = parse_single_command(tokens);
	if (!cmd)
		return (NULL);
	cmd->start = cmd;
	return (cmd);
}
