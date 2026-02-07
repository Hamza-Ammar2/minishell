/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haammar <haammar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 22:39:09 by lpons             #+#    #+#             */
/*   Updated: 2026/02/07 08:46:55 by haammar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*duplicate;

	len = ft_strlen(s1);
	duplicate = malloc(len + 1);
	if (!duplicate)
		return (NULL);
	ft_strlcpy(duplicate, s1, len + 1);
	return (duplicate);
}
