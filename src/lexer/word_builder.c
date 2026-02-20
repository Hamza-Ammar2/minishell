/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_builder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpons <lpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 02:45:44 by lpons             #+#    #+#             */
/*   Updated: 2026/01/24 03:04:26 by lpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/libft.h"

static char	*append_segment(char *word, const char *segment)
{
	char	*result;

	if (!word)
		return (ft_strdup(segment));
	if (!segment || !*segment)
		return (word);
	result = ft_strjoin(word, segment);
	free(word);
	return (result);
}

static int	extract_unquoted_part(const char *input, char **result)
{
	int		len;
	char	*segment;

	len = 0;
	while (input[len] && !ft_isspace(input[len])
		&& !is_operator((char *)&input[len]) && !is_quote(input[len]))
		len++;
	if (len == 0)
		return (0);
	segment = ft_substr(input, 0, len);
	if (!segment)
		return (-1);
	*result = append_segment(*result, segment);
	free(segment);
	if (!*result)
		return (-1);
	return (len);
}

static int	process_quoted_part(const char *input, int *i, char **word,
		int *quote_type)
{
	char	*quoted_part;
	int		temp_quote_type;

	quoted_part = extract_quoted_word(input, i, &temp_quote_type);
	if (!quoted_part)
		return (0);
	if (*quote_type == QUOTE_NONE)
		*quote_type = temp_quote_type;
	*word = append_segment(*word, quoted_part);
	free(quoted_part);
	if (!*word)
		return (0);
	return (1);
}

char	*extract_complete_word(const char *input, int *i, int *quote_type)
{
	char	*word;
	int		len;

	word = NULL;
	*quote_type = QUOTE_NONE;
	while (input[*i] && !ft_isspace(input[*i])
		&& !is_operator((char *)&input[*i]))
	{
		if (is_quote(input[*i]))
		{
			if (!process_quoted_part(input, i, &word, quote_type))
				return (free(word), NULL);
		}
		else
		{
			len = extract_unquoted_part(&input[*i], &word);
			if (len < 0)
				return (free(word), NULL);
			*i += len;
		}
	}
	return (word);
}
