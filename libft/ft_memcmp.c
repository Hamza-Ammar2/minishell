/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haammar <haammar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 21:16:29 by lpons             #+#    #+#             */
/*   Updated: 2026/02/07 08:47:57 by haammar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*d1 = (const unsigned char *)s1;
	const unsigned char	*d2 = (const unsigned char *)s2;

	i = 0;
	while (i < n)
	{
		if (d1[i] != d2[i])
			return ((int)d1[i] - (int)d2[i]);
		i++;
	}
	return (0);
}
