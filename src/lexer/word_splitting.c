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
** WORD SPLITTING IMPLEMENTATION
** =============================
** This file implements word splitting for unquoted variable expansions.
** 
** WHAT IS WORD SPLITTING?
** When a variable is expanded WITHOUT quotes, the result should be split
** on whitespace into multiple words/arguments.
** 
** Example:
**   VAR="one two three"
**   echo $VAR      -> 3 arguments: "one", "two", "three"
**   echo "$VAR"    -> 1 argument: "one two three"
**
** HOW IT WORKS (Tokenize -> Expand -> Re-tokenize pattern):
** 1. After tokenizing, we iterate through all WORD tokens
** 2. For each token, expand variables ($VAR -> value)
** 3. If token was UNQUOTED (quote_type == QUOTE_NONE) and expanded
**    value contains whitespace, split into multiple tokens
** 4. If token was QUOTED, keep as single token (no splitting)
*/

/*
** 🔧 What it Does
** Checks if a string contains any whitespace characters.
**
** 🔗 Role
** Helper to determine if word splitting is needed after expansion.
**
** WHY: We only split tokens that have whitespace in their expanded value.
*/
static int	has_whitespace(const char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (ft_isspace(*str))
			return (1);
		str++;
	}
	return (0);
}

/*
** 🔧 What it Does
** Creates a linked list of tokens from an array of split strings.
**
** 🔗 Role
** Converts the result of ft_split into token nodes.
**
** WHY: After splitting "one two three" into ["one", "two", "three"],
** we need to convert each into a t_token for the parser.
*/
static t_token	*create_split_tokens(char **splits, t_token *tail)
{
	t_token	*head;
	t_token	*new;
	t_token	*last;
	int		i;

	head = NULL;
	last = NULL;
	i = 0;
	while (splits[i])
	{
		/* WORD SPLIT: Each split part becomes its own token.
		** quote_type = QUOTE_NONE since these are split words. */
		new = new_token(TOKEN_WORD, splits[i], QUOTE_NONE);
		if (!new)
			return (free_tokens(head), NULL);
		if (!head)
			head = new;
		else
			last->next = new;
		last = new;
		i++;
	}
	if (last)
		last->next = tail;
	return (head);
}

/*
** 🔧 What it Does
** Expands a token and splits if unquoted with whitespace.
**
** 🔗 Role
** Core word splitting logic for a single token.
**
** WHY: This is where the actual word splitting decision happens.
** Only UNQUOTED tokens with whitespace in their expanded value get split.
**
** Returns: Pointer to replacement tokens (or original if no split needed).
** Sets *should_free to 1 if original token should be freed.
*/
static t_token	*process_word_token(t_shell *shell, t_token *tok,
		int *should_free)
{
	char	*expanded;
	char	**splits;
	t_token	*new_tokens;

	*should_free = 0;
	if (tok->type != TOKEN_WORD || !tok->value)
		return (tok);
	/* Expand variables in the token value */
	expanded = expand_str(shell, tok->value, tok->quote_type);
	if (!expanded)
		return (tok);
	/* WORD SPLIT DECISION:
	** - If token was QUOTED, NO splitting (quotes prevent it)
	** - If expanded value has no whitespace, NO splitting needed
	** - Otherwise, SPLIT on whitespace into multiple tokens */
	if (tok->quote_type != QUOTE_NONE || !has_whitespace(expanded))
	{
		/* No split - just update the value */
		free(tok->value);
		tok->value = expanded;
		return (tok);
	}
	/* WORD SPLIT: Unquoted token with whitespace in expanded value */
	splits = ft_split(expanded, ' ');
	free(expanded);
	if (!splits || !splits[0])
	{
		/* Empty expansion - mark for removal */
		free_splits(splits);
		*should_free = 1;
		return (NULL);
	}
	/* Create new tokens from split parts, linking to tok->next */
	new_tokens = create_split_tokens(splits, tok->next);
	free_splits(splits);
	*should_free = 1;
	if (!new_tokens)
		return (tok);
	return (new_tokens);
}

/*
** 🔧 What it Does
** Expands all tokens and performs word splitting on unquoted expansions.
**
** 🔗 Role
** Main entry point for word splitting. Called after tokenizing,
** before parsing.
**
** WHY: Implements the "Tokenize -> Expand -> Re-tokenize" pattern.
** This is called from process_input() after tokenize() but before parse().
**
** Returns: New head of token list (may change if first token was split).
*/
t_token	*expand_and_split_tokens(t_shell *shell, t_token *tokens)
{
	t_token	*head;
	t_token	*current;
	t_token	*prev;
	t_token	*processed;
	t_token	*next_tok;
	int		should_free;

	if (!tokens)
		return (NULL);
	head = NULL;
	prev = NULL;
	current = tokens;
	while (current)
	{
		/* Save next pointer before potentially freeing current */
		next_tok = current->next;
		processed = process_word_token(shell, current, &should_free);
		if (should_free)
		{
			/* Token was split or removed - free original */
			if (prev)
				prev->next = processed;
			else
				head = processed;
			free(current->value);
			free(current);
			/* Find end of inserted tokens to continue */
			if (processed)
			{
				while (processed->next && processed->next != next_tok)
					processed = processed->next;
				prev = processed;
				current = processed->next;
			}
			else
				current = (prev ? prev->next : head);
		}
		else
		{
			/* Token was just expanded (no split) */
			if (!head)
				head = processed;
			prev = processed;
			current = processed->next;
		}
	}
	return (head);
}
