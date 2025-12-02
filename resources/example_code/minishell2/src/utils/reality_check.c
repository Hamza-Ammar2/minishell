/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reality_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorth <aorth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 00:21:31 by aorth             #+#    #+#             */
/*   Updated: 2025/06/30 15:04:31 by aorth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	reality_check(char *input)
{
	int	i;
	int	flag;

	flag = 0;
	if (!input[0])
	{
		free(input);
		return (0);
	}
	i = 0;
	if (!ft_isalnum(input[0] && !input[1] && !flag) && input[0] != ' ')
		return (1);
	while (input[i] && !ft_isalnum(input[i]))
	{
		if (input[i] == ' ' || input[i] == '\t')
			i++;
		else if (input[i] == '\n' || input[i] == '\r')
			return (free(input), 0);
		else
			i++;
	}
	if (!input[i])
		return (free(input), 0);
	return (1);
}
