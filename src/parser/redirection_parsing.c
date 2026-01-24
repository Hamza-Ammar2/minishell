/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_parsing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpons <lpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 03:05:17 by lpons             #+#    #+#             */
/*   Updated: 2026/01/24 03:24:29 by lpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** 🔧 What the function Does
** Creates a new merged redirect token.
**
** 🔗 Role in the Program
** Helper to combine operator type with filename value.
**
** 🧩 Step-by-Step
** 1. Take operator type from redirect token.
** 2. Take filename value from filename token.
** 3. Create new token with combined properties.
*/
static t_token	*create_redirect_token(t_token_type type,
		t_token *filename_token)
{
	return (new_token(type, filename_token->value, filename_token->quote_type));
}

/*
** 🔧 What the function Does
** Extracts all redirect operators and filenames into merged token list.
**
** 🔗 Role in the Program
** Transforms redirect operator+filename pairs into single tokens for executor.
**
** 🧩 Step-by-Step
** 1. Traverse input tokens.
** 2. When redirect operator found, merge with next token's filename.
** 3. Create new token with operator type + filename value.
** 4. Add to redirect list and skip filename token.
** 5. Return list of merged redirect tokens.
*/
t_token	*extract_redirections(t_token *tokens)
{
	t_token	*rdr_tokens;
	t_token	*redirect;

	rdr_tokens = NULL;
	while (tokens)
	{
		if (is_redirect_type(tokens->type))
		{
			if (!tokens->next)
				return (NULL);
			redirect = create_redirect_token(tokens->type, tokens->next);
			add_token_to_list(&rdr_tokens, redirect);
			tokens = tokens->next;
		}
		tokens = tokens->next;
	}
	return (rdr_tokens);
}

/*
** 🔧 What the function Does
** Extracts redirect tokens and attaches them to command.
**
** 🔗 Role in the Program
** Parses redirections from token list and stores in command structure.
**
** 🧩 Step-by-Step
** 1. Call extract_redirections to get merged redirect tokens.
** 2. Store result in cmd->redirects field.
*/
void	parse_redirections(t_command *cmd, t_token *tokens)
{
	cmd->redirects = extract_redirections(tokens);
}
