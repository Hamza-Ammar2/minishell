/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_validator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpons <lpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 03:05:21 by lpons             #+#    #+#             */
/*   Updated: 2026/01/25 14:56:18 by lpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_operator_token(t_token_type type)
{
	return (type == TOKEN_PIPE || type == TOKEN_REDIRECT_IN
		|| type == TOKEN_REDIRECT_OUT || type == TOKEN_REDIRECT_APPEND
		|| type == TOKEN_REDIRECT_HEREDOC);
}

static int	validate_start(t_token *tokens)
{
	if (!tokens)
		return (1);
	if (tokens->type == TOKEN_PIPE)
	{
		ft_fprintf(2, "minishell: syntax error near unexpected token `|'\n");
		return (0);
	}
	return (1);
}

static int	validate_end(t_token *tokens)
{
	t_token	*last;

	if (!tokens)
		return (1);
	last = get_last_token(tokens);
	if (is_operator_token(last->type))
	{
		ft_fprintf(2,
			"minishell: syntax error near unexpected token `newline'\n");
		return (0);
	}
	return (1);
}

static int	validate_consecutive(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current && current->next)
	{
		if (is_redirect_type(current->type)
			&& current->next->type != TOKEN_WORD)
			return (ft_fprintf(2,
					"minishell: syntax error: redirect needs filename\n"), 0);
		current = current->next;
	}
	return (1);
}

int	validate_syntax(t_token *tokens)
{
	if (!tokens)
		return (1);
	if (!validate_start(tokens))
		return (0);
	if (!validate_end(tokens))
		return (0);
	if (!validate_consecutive(tokens))
		return (0);
	return (1);
}
