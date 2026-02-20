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

static void	link_command(t_command **head, t_command **current, t_command *new)
{
	if (!*head)
		*head = new;
	else
		(*current)->next = new;
	*current = new;
}

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
