/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpons <lpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 03:02:55 by lpons             #+#    #+#             */
/*   Updated: 2026/01/24 03:02:55 by lpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

char	**append_word(char **arr, char *str)
{
	char	**new_arr;
	int		i;

	i = 0;
	if (!str)
		return (perror("could not append string"), free_splits(arr), NULL);
	while (arr && arr[i])
		i++;
	new_arr = malloc(sizeof(char *) * (i + 2));
	if (!new_arr)
		return (perror("could not append string"), free_splits(arr), NULL);
	i = 0;
	while (arr && arr[i])
	{
		new_arr[i] = arr[i];
		i++;
	}
	new_arr[i] = str;
	new_arr[i + 1] = NULL;
	if (arr)
		free(arr);
	return (new_arr);
}

static int	quote2type(char c)
{
	if (c == '\'')
		return (1);
	if (c == '\"')
		return (2);
	return (0);
}

static int	dumb(char ***words, char *str, int *start, int *end)
{
	if (!quote2type(str[*end]) && str[*end] != ' ')
		(*end)++;
	else if (str[*end] == ' ')
	{
		if (*end <= *start)
		{
			(*end)++;
			*start = *end;
			return (1);
		}
		*words = append_word(*words,
				ft_substr(str, *start, *end - *start));
		if (!*words)
			return (0);
		(*end)++;
		*start = *end;
	}
	else
		*end = ft_strchr(str + *end + 1, str[*end]) - str + 1;
	return (1);
}

char	**extract_words(char **words, char *str)
{
	int		start;
	int		end;

	start = 0;
	end = 0;
	while (str[end])
	{
		if (!dumb(&words, str, &start, &end))
			return (NULL);
	}
	if (end > start)
		words = append_word(words, ft_substr(str, start, end - start));
	else if (end == start && !*str)
		return (words = append_word(words, ft_strdup("")));
	return (words);
}
