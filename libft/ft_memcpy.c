/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haammar <haammar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 21:14:33 by lpons             #+#    #+#             */
/*   Updated: 2026/02/07 08:47:51 by haammar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *target, const void *source, size_t n)
{
	size_t				i;
	unsigned char		*d;
	const unsigned char	*s;

	if (target == source || n == 0)
		return (target);
	d = (unsigned char *)target;
	s = (const unsigned char *)source;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (target);
}
