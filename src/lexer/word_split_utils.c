/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_split_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpons <lpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 00:00:00 by lpons             #+#    #+#             */
/*   Updated: 2026/02/16 00:00:00 by lpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

/* Checks if string contains whitespace (for word split decision) */
int	has_whitespace(const char *str)
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

/* Adds a token to the end of a result list, returns new tail */
t_token	*append_token(t_token **head, t_token *tail, t_token *new)
{
	if (!*head)
		*head = new;
	else
		tail->next = new;
	return (new);
}

/* Creates tokens from split strings and appends to result list */
t_token	*append_split_tokens(t_token **head, t_token *tail, char **splits)
{
	t_token	*new;
	int		i;

	i = 0;
	while (splits[i])
	{
		new = new_token(TOKEN_WORD, splits[i], QUOTE_NONE);
		if (!new)
			return (NULL);
		tail = append_token(head, tail, new);
		i++;
	}
	return (tail);
}

/* Expands token value and decides whether to split */
char	*expand_token_value(t_shell *shell, t_token *tok)
{
	return (expand_str(shell, tok->value, tok->quote_type));
}

/* Checks if token should be word-split (unquoted + has whitespace) */
int	should_split(t_token *tok, char *expanded)
{
	if (tok->quote_type != QUOTE_NONE)
		return (0);
	return (has_whitespace(expanded));
}
