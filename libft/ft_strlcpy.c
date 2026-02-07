/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haammar <haammar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 21:15:17 by lpons             #+#    #+#             */
/*   Updated: 2026/02/07 08:46:30 by haammar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *target, const char *source, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (source[i])
		i++;
	if (size > 0)
	{
		while (source[j] && j < size - 1)
		{
			target[j] = source[j];
			j++;
		}
		target[j] = '\0';
	}
	return (i);
}
