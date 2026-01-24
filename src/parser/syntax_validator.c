/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_validator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpons <lpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 03:05:21 by lpons             #+#    #+#             */
/*   Updated: 2026/01/24 19:48:28 by lpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** 🔧 What the function Does
** Checks if token is an operator type.
**
** 🔗 Role in the Program
** Helper for syntax validation and parsing.
**
** 🧩 Step-by-Step
** 1. Check if token type is any operator.
** 2. Return 1 if operator, 0 if not.
*/
int	is_operator_token(t_token_type type)
{
	return (type == TOKEN_PIPE || type == TOKEN_REDIRECT_IN
		|| type == TOKEN_REDIRECT_OUT || type == TOKEN_REDIRECT_APPEND
		|| type == TOKEN_REDIRECT_HEREDOC);
}

/*
** 🔧 What the function Does
** Checks if command starts with a pipe operator (invalid).
**
** 🔗 Role in the Program
** Validates token list doesn't start with pipe.
** Note: Starting with redirections (< > << >>) is valid in bash.
**
** 🧩 Step-by-Step
** 1. Check if first token is a pipe.
** 2. Print error if invalid.
** 3. Return 0 for invalid, 1 for valid.
*/
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

/*
** 🔧 What the function Does
** Checks if command ends with an operator (invalid).
**
** 🔗 Role in the Program
** Validates token list doesn't end with operator.
**
** 🧩 Step-by-Step
** 1. Find last token.
** 2. Check if it's an operator.
** 3. Print error if invalid.
** 4. Return 0 for invalid, 1 for valid.
*/
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

/*
** 🔧 What the function Does
** Checks for invalid consecutive operators.
**
** 🔗 Role in the Program
** Validates operator sequences are valid.
** Note: Consecutive redirects like "< file1 < file2" are valid.
**       But "| |" or "|  <" at start of pipe segment are invalid.
**
** 🧩 Step-by-Step
** 1. Traverse token list.
** 2. Check if current is redirect and next is not a word.
** 3. Check if current is pipe and next is also pipe or redirect.
** 4. Print error if invalid sequence found.
** 5. Return 0 for invalid, 1 for valid.
*/
static int	validate_consecutive(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current && current->next)
	{
		if (current->type == TOKEN_PIPE)
		{
			if (is_operator_token(current->next->type))
				return (ft_fprintf(2,
						"syntax error near unexpected token\n"), 0);
		}
		else if (is_redirect_type(current->type))
		{
			if (current->next->type != TOKEN_WORD)
				return (ft_fprintf(2,
						"syntax error: redirect needs filename\n"), 0);
		}
		current = current->next;
	}
	return (1);
}

/*
** 🔧 What the function Does
** Validates token list syntax before parsing.
**
** 🔗 Role in the Program
** Ensures token sequence is valid before attempting to parse/execute.
**
** 🧩 Step-by-Step
** 1. Check tokens don't start with operator.
** 2. Check tokens don't end with operator.
** 3. Check no consecutive operators.
** 4. Check pipe syntax is valid.
** 5. Check redirection syntax is valid.
** 6. Return 1 if all valid, 0 if any invalid.
*/
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
