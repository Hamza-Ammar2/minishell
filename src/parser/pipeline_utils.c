/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpons <lpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 00:00:00 by lpons             #+#    #+#             */
/*   Updated: 2026/01/24 03:18:58 by lpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** 🔧 What the function Does
** Counts the number of pipe tokens in a token list.
**
** 🔗 Role in the Program
** Determines if input contains a pipeline and how many commands exist.
**
** 🧩 Step-by-Step
** 1. Traverse token list.
** 2. Count TOKEN_PIPE tokens.
** 3. Return total count.
*/
int	count_pipes(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens)
	{
		if (tokens->type == TOKEN_PIPE)
			i++;
		tokens = tokens->next;
	}
	return (i);
}

/*
** 🔧 What the function Does
** Locates the next pipe token in the list.
**
** 🔗 Role in the Program
** Helper for traversing and splitting commands at pipe boundaries.
**
** 🧩 Step-by-Step
** 1. Traverse tokens until pipe found.
** 2. Return pointer to pipe token.
** 3. Return NULL if no pipe exists.
*/
t_token	*find_next_pipe(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == TOKEN_PIPE)
			return (tokens);
		tokens = tokens->next;
	}
	return (NULL);
}
