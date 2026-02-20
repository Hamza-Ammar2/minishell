/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpons <lpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 02:45:38 by lpons             #+#    #+#             */
/*   Updated: 2026/01/24 03:06:52 by lpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*is_operator(char *str)
{
	if (*str == '|')
		return ("|");
	if (*str == '<' && *(str + 1) == '<')
		return ("<<");
	if (*str == '<')
		return ("<");
	if (*str == '>' && *(str + 1) == '>')
		return (">>");
	if (*str == '>')
		return (">");
	return (NULL);
}

t_token_type	get_token_type(char *op)
{
	if (ft_strcmp(op, "|") == 0)
		return (TOKEN_PIPE);
	if (ft_strcmp(op, "<") == 0)
		return (TOKEN_REDIRECT_IN);
	if (ft_strcmp(op, ">") == 0)
		return (TOKEN_REDIRECT_OUT);
	if (ft_strcmp(op, ">>") == 0)
		return (TOKEN_REDIRECT_APPEND);
	if (ft_strcmp(op, "<<") == 0)
		return (TOKEN_REDIRECT_HEREDOC);
	return (TOKEN_WORD);
}

static int	process_operator(t_token **head, char *operator)
{
	t_token	*token;

	token = new_token(get_token_type(operator), NULL, 0);
	add_token_to_list(head, token);
	return (ft_strlen(operator));
}

static int	process_complete_word(t_token **head, char *input, int *i)
{
	t_token	*token;
	char	*word;
	int		quote_type;

	word = extract_complete_word(input, i, &quote_type);
	if (!word)
		return (0);
	token = new_token(TOKEN_WORD, word, quote_type);
	add_token_to_list(head, token);
	free(word);
	return (1);
}

t_token	*tokenize(char *input)
{
	t_token	*head;
	char	*operator;
	int		i;

	head = NULL;
	i = 0;
	while (input[i])
	{
		while (input[i] && ft_isspace(input[i]))
			i++;
		if (!input[i])
			break ;
		operator = is_operator(&input[i]);
		if (operator)
		{
			i += process_operator(&head, operator);
		}
		else
		{
			if (!process_complete_word(&head, input, &i))
				return (free_tokens(head), NULL);
		}
	}
	return (head);
}
