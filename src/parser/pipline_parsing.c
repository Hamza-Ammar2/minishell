/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipline_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpons <lpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 03:05:13 by lpons             #+#    #+#             */
/*   Updated: 2026/01/24 03:18:57 by lpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** 🔧 What the function Does
** Extracts tokens up to the next pipe, creating a copy.
**
** 🔗 Role in the Program
** Isolates tokens for a single command segment from pipeline.
**
** 🧩 Step-by-Step
** 1. Copy tokens until pipe or end is reached.
** 2. Advance original token pointer past the extracted segment.
** 3. Skip pipe token if present.
** 4. Return copied token list for the command.
*/
t_token	*extract_command_tokens(t_token **tokens)
{
	t_token	*head;
	t_token	*copy;

	head = NULL;
	while (*tokens && (*tokens)->type != TOKEN_PIPE)
	{
		copy = new_token((*tokens)->type, (*tokens)->value,
				(*tokens)->quote_type);
		add_token_to_list(&head, copy);
		*tokens = (*tokens)->next;
	}
	if (*tokens)
		*tokens = (*tokens)->next;
	return (head);
}

/*
** 🔧 What the function Does
** Fills command args array with token values, skipping redirects.
**
** 🔗 Role in the Program
** Extracts executable command and arguments from token list.
**
** 🧩 Step-by-Step
** 1. Traverse tokens until pipe or end.
** 2. Copy WORD token values to args array.
** 3. Skip redirect operators and their filenames.
** 4. NULL-terminate the args array.
*/
static int	fill_command_args(t_command *cmd, t_token *tokens)
{
	int		i;
	t_token	*tmp;

	i = 0;
	tmp = tokens;
	while (tmp && tmp->type != TOKEN_PIPE)
	{
		if (tmp->type == TOKEN_WORD)
		{
			cmd->args[i] = new_token(TOKEN_WORD, tmp->value, tmp->quote_type);
			if (!cmd->args[i])
				return (-1);
			i++;
		}
		else if (is_redirect_type(tmp->type))
		{
			if (tmp->next)
				tmp = tmp->next;
		}
		tmp = tmp->next;
	}
	cmd->args[i] = NULL;
	return (0);
}

/*
** 🔧 What the function Does
** Creates a command structure from a token list segment.
**
** 🔗 Role in the Program
** Converts tokens for one command into executable command structure.
**
** 🧩 Step-by-Step
** 1. Allocate new command structure.
** 2. Parse and attach redirections.
** 3. Count arguments (excluding redirects).
** 4. Allocate args array.
** 5. Fill args with token values.
** 6. Return completed command.
*/
static t_command	*create_pipeline_command(t_token *cmd_tokens)
{
	t_command	*cmd;
	int			arg_count;

	cmd = new_command();
	if (!cmd)
		return (NULL);
	parse_redirections(cmd, cmd_tokens);
	arg_count = count_args(cmd_tokens);
	cmd->args = malloc(sizeof(t_token *) * (arg_count + 1));
	if (!cmd->args)
	{
		free_commands(cmd);
		return (NULL);
	}
	if (fill_command_args(cmd, cmd_tokens) == -1)
	{
		free_commands(cmd);
		return (NULL);
	}
	return (cmd);
}

/*
** 🔧 What the function Does
** Links a new command into the pipeline chain.
**
** 🔗 Role in the Program
** Maintains linked list of commands in pipeline order.
**
** 🧩 Step-by-Step
** 1. If first command, set as head.
** 2. Otherwise, link to previous command's next.
** 3. Update current pointer to new command.
*/
static void	link_command(t_command **head, t_command **current, t_command *new)
{
	if (!*head)
		*head = new;
	else
		(*current)->next = new;
	*current = new;
}

/*
** 🔧 What the function Does
** Parses token list into linked command structures for pipeline.
**
** 🔗 Role in the Program
** Main pipeline parser - converts tokens into executable command chain.
**
** 🧩 Step-by-Step
** 1. Create working copy of token pointer.
** 2. Loop through tokens, extracting command segments.
** 3. Create command structure for each segment.
** 4. Link commands into pipeline chain.
** 5. Return head of command list for executor.
*/
t_command	*parse_pipeline(t_token *tokens)
{
	t_command	*head;
	t_command	*current;
	t_command	*new_cmd;
	t_token		*cmd_tokens;
	t_token		*token_copy;

	head = NULL;
	current = NULL;
	token_copy = tokens;
	while (token_copy)
	{
		cmd_tokens = extract_command_tokens(&token_copy);
		if (!cmd_tokens)
			break ;
		new_cmd = create_pipeline_command(cmd_tokens);
		free_tokens(cmd_tokens);
		if (!new_cmd)
			return (free_commands(head), NULL);
		link_command(&head, &current, new_cmd);
	}
	set_pipeline_start(head);
	return (head);
}
