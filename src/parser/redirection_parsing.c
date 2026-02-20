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

static t_token	*create_redirect_token(t_token_type type,
		t_token *filename_token)
{
	return (new_token(type, filename_token->value, filename_token->quote_type));
}

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

void	parse_redirections(t_command *cmd, t_token *tokens)
{
	cmd->redirects = extract_redirections(tokens);
}
