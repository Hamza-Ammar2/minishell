/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpons <lpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 02:44:57 by lpons             #+#    #+#             */
/*   Updated: 2026/01/24 03:00:09 by lpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

/*
** Called from: tokenize() in tokenizer.c
** Purpose: Check if current character is a quote
** Example: is_quote(input[i]) where i is the current position
*/
int	is_quote(char c)
{
	return (c == 34 || c == 39);
}

/*
** Called from: extract_quoted_word() below
** Purpose: Find the index of the matching closing quote
** Parameters:
**   - str: string starting AFTER the opening quote
**   - quote: the quote character to match (' or ")
** Returns: index of closing quote, or -1 if not found
** Example: find_closing_quote(&input[i + 1], '\'')
*/
int	find_closing_quote(const char *str, char quote)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == quote)
			return (i);
		i++;
	}
	return (-1);
}

/*
** Called from: tokenize() in tokenizer.c
** Purpose: Extract a quoted string (with quotes included)
** Parameters:
**   - input: full input string
**   - i: pointer to current position (will be updated)
**   - quote_type: pointer to store 1 (single) or 2 (double)
** Returns: allocated string WITH QUOTES INCLUDED as literals, or NULL on error
** Example: extract_quoted_word(input, &i, &quote_type)
** FIX: Keep quotes as literal characters - exec will handle quote removal
*/
char	*extract_quoted_word(const char *input, int *i, int *quote_type)
{
	char	quote;
	int		close_pos;
	char	*string;

	quote = input[*i];
	if (quote == 39)
		*quote_type = QUOTE_SINGLE;
	else
		*quote_type = QUOTE_DOUBLE;
	close_pos = find_closing_quote(&input[*i + 1], quote);
	if (close_pos == -1)
	{
		ft_putstr_fd("minishell: syntax error: unclosed quote\n", 2);
		return (NULL);
	}
	string = ft_substr(input, *i, close_pos + 2);
	if (!string)
		return (NULL);
	*i += close_pos + 2;
	return (string);
}
