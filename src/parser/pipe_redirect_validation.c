/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redirect_validation.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpons <lpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 03:05:10 by lpons             #+#    #+#             */
/*   Updated: 2026/01/24 19:45:14 by lpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_redirect_type(t_token_type type)
{
	return (type == TOKEN_REDIRECT_IN || type == TOKEN_REDIRECT_OUT
		|| type == TOKEN_REDIRECT_APPEND || type == TOKEN_REDIRECT_HEREDOC);
}

static int	validate_pipe_boundaries(t_token *tokens)
{
	t_token	*last;

	if (tokens->type == TOKEN_PIPE)
	{
		ft_fprintf(2, "minishell: syntax error near unexpected token `|'\n");
		return (0);
	}
	last = get_last_token(tokens);
	if (last->type == TOKEN_PIPE)
	{
		ft_fprintf(2,
			"minishell: syntax error near unexpected token `newline'\n");
		return (0);
	}
	return (1);
}

static int	validate_consecutive_pipes(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current && current->next)
	{
		if (current->type == TOKEN_PIPE && current->next->type == TOKEN_PIPE)
		{
			ft_fprintf(2,
				"minishell: syntax error near unexpected token `|'\n");
			return (0);
		}
		current = current->next;
	}
	return (1);
}

int	validate_pipe_syntax(t_token *tokens)
{
	if (!tokens)
		return (1);
	if (!validate_pipe_boundaries(tokens))
		return (0);
	if (!validate_consecutive_pipes(tokens))
		return (0);
	return (1);
}

int	validate_redirection_syntax(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (is_redirect_type(current->type))
		{
			if (!current->next)
			{
				return (0);
			}
			if (current->next->type != TOKEN_WORD)
			{
				return (0);
			}
		}
		current = current->next;
	}
	return (1);
}
