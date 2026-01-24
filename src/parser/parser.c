/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpons <lpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 03:05:06 by lpons             #+#    #+#             */
/*   Updated: 2026/01/25 00:38:28 by lpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** 🔧 What the function Does
** Counts the number of WORD tokens until pipe or end.
**
** 🔗 Role in the Program
** Helper to determine args array size during parsing.
**
** 🧩 Step-by-Step
** 1. Traverse token list.
** 2. Count TOKEN_WORD tokens.
** 3. Skip redirect operators and their filenames.
** 4. Stop at pipe or end.
*/
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

/*
** 🔧 What the function Does
** Fills the args array with token values, skipping redirects.
**
** 🔗 Role in the Program
** Extracts WORD token values into command args array.
**
** 🧩 Step-by-Step
** 1. Traverse token list.
** 2. Copy WORD token values to args array.
** 3. Skip redirect operators and their filenames.
** 4. NULL-terminate the array.
*/
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

/*
** 🔧 What the function Does
** Parses single command (no pipes).
**
** 🔗 Role in the Program
** Handles simple commands without pipelines.
**
** 🧩 Step-by-Step
** 1. Create new command structure.
** 2. Parse and attach redirections.
** 3. Count and allocate args array.
** 4. Fill args array with token values.
** 5. Return parsed command structure.
*/
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

/*
** 🔧 What the function Does
** Routes to pipeline or single command parser.
**
** 🔗 Role in the Program
** Main entry point for parsing tokens into commands.
**
** 🧩 Step-by-Step
** 1. Check if tokens contain pipes.
** 2. Route to parse_pipeline() if pipes exist.
** 3. Otherwise parse as single command.
*/
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
