/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haammar <haammar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 22:40:04 by lpons             #+#    #+#             */
/*   Updated: 2026/02/07 08:45:47 by haammar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	strlen;
	char	*substr;

	if (!s)
		return (NULL);
	strlen = ft_strlen(s);
	if (start >= strlen)
		return (ft_strdup(""));
	if (len > strlen - start)
		len = strlen - start;
	substr = malloc(len + 1);
	if (!substr)
		return (NULL);
	ft_strlcpy(substr, s + start, len + 1);
	return (substr);
}
