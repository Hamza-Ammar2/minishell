/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haammar <haammar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 21:14:47 by lpons             #+#    #+#             */
/*   Updated: 2026/02/07 08:47:41 by haammar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*pointer;
	unsigned char	fill;

	pointer = (unsigned char *)s;
	fill = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		pointer[i] = fill;
		i++;
	}
	return (s);
}
