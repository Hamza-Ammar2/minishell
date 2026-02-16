/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_splitting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpons <lpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 00:00:00 by lpons             #+#    #+#             */
/*   Updated: 2026/02/16 00:00:00 by lpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

/*
** WORD SPLITTING: Expands $VAR and splits unquoted results on whitespace.
** Called after tokenize(), before parse().
** Example: VAR="a b"; echo $VAR -> tokens: [echo] [a] [b]
*/

/* Handles split case: creates multiple tokens from expanded value */
static t_token	*handle_split(t_token **head, t_token *tail, char *expanded)
{
	char	**splits;
	t_token	*new_tail;

	splits = ft_split(expanded, ' ');
	free(expanded);
	if (!splits || !splits[0])
	{
		free_splits(splits);
		return (tail);
	}
	new_tail = append_split_tokens(head, tail, splits);
	free_splits(splits);
	return (new_tail);
}

/* Handles no-split case: creates single token with expanded value */
static t_token	*handle_no_split(t_token **head, t_token *tail, char *expanded)
{
	t_token	*new;

	new = new_token(TOKEN_WORD, expanded, QUOTE_NONE);
	free(expanded);
	if (!new)
		return (NULL);
	return (append_token(head, tail, new));
}

/* Processes a single token: expand and optionally split */
static t_token	*process_token(t_shell *shell, t_token *tok,
		t_token **head, t_token *tail)
{
	char	*expanded;

	if (tok->type != TOKEN_WORD)
	{
		return (append_token(head, tail,
				new_token(tok->type, tok->value, tok->quote_type)));
	}
	expanded = expand_token_value(shell, tok);
	if (!expanded)
		return (NULL);
	if (should_split(tok, expanded))
		return (handle_split(head, tail, expanded));
	return (handle_no_split(head, tail, expanded));
}

/* Main entry: expands all tokens and splits unquoted expansions */
t_token	*expand_and_split_tokens(t_shell *shell, t_token *tokens)
{
	t_token	*head;
	t_token	*tail;
	t_token	*current;

	head = NULL;
	tail = NULL;
	current = tokens;
	while (current)
	{
		tail = process_token(shell, current, &head, tail);
		if (!tail && head)
		{
			free_tokens(head);
			free_tokens(tokens);
			return (NULL);
		}
		current = current->next;
	}
	free_tokens(tokens);
	return (head);
}
