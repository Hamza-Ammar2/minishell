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

/*
** 🔧 What the function Does
** Checks if token type is a redirection operator.
**
** 🔗 Role in the Program
** Helper for redirection syntax validation.
**
** 🧩 Step-by-Step
** 1. Check if token type is any redirect operator.
** 2. Return 1 if redirect, 0 if not.
*/
int	is_redirect_type(t_token_type type)
{
	return (type == TOKEN_REDIRECT_IN || type == TOKEN_REDIRECT_OUT
		|| type == TOKEN_REDIRECT_APPEND || type == TOKEN_REDIRECT_HEREDOC);
}

/*
** 🔧 What the function Does
** Checks if token list starts or ends with pipe.
**
** 🔗 Role in the Program
** Helper for pipe syntax validation.
**
** 🧩 Step-by-Step
** 1. Check first token is not pipe.
** 2. Check last token is not pipe.
** 3. Return 1 if valid, 0 if error.
*/
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

/*
** 🔧 What the function Does
** Checks for consecutive pipe operators.
**
** 🔗 Role in the Program
** Helper for pipe syntax validation.
**
** 🧩 Step-by-Step
** 1. Traverse token list.
** 2. Check if current and next are both pipes.
** 3. Return 1 if valid, 0 if error.
*/
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

/*
** 🔧 What the function Does
** Validates pipe operator placement in token list.
**
** 🔗 Role in the Program
** Ensures pipes have commands before and after them.
**
** 🧩 Step-by-Step
** 1. Check first/last token not pipe.
** 2. Check no consecutive pipes.
** 3. Return 1 if valid, 0 if error.
*/
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

/*
** 🔧 What the function Does
** Validates redirection operators have filenames.
**
** 🔗 Role in the Program
** Ensures every <, >, >>, << has a filename/delimiter after it.
**
** 🧩 Step-by-Step
** 1. Loop through all tokens.
** 2. For each redirect operator, check next token exists.
** 3. Check next token is WORD type.
** 4. Return 1 if valid, 0 if error.
*/
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
