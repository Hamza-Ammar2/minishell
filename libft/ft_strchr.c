/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haammar <haammar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 21:14:56 by lpons             #+#    #+#             */
/*   Updated: 2026/02/07 08:47:03 by haammar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*p;

	p = (char *)s;
	while (*p != '\0')
	{
		if (*p == (char)c)
		{
			return (p);
		}
		p++;
	}
	if ((char)c == '\0')
	{
		return (p);
	}
	return (NULL);
}
