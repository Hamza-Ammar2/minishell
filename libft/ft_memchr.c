/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haammar <haammar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 22:38:24 by lpons             #+#    #+#             */
/*   Updated: 2026/02/07 08:48:04 by haammar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*pointer;

	pointer = (const unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (pointer[i] == (unsigned char)c)
		{
			return ((void *)(pointer + i));
		}
		i++;
	}
	return (NULL);
}
