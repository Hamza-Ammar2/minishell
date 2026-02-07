/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haammar <haammar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 22:36:54 by lpons             #+#    #+#             */
/*   Updated: 2026/02/07 08:49:17 by haammar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	total;
	void	*pointer;

	total = count * size;
	if (size != 0 && total / size != count)
		return (NULL);
	pointer = malloc(total);
	if (pointer == NULL)
		return (NULL);
	ft_bzero(pointer, total);
	return (pointer);
}
