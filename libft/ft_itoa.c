/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haammar <haammar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 22:37:21 by lpons             #+#    #+#             */
/*   Updated: 2026/02/07 08:48:49 by haammar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(long n)
{
	int	len;

	len = (n <= 0);
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	long	nb;
	int		len;
	char	*string;

	nb = (long)n;
	len = count_digits(nb);
	string = malloc(len + 1);
	if (!string)
		return (NULL);
	string[len] = '\0';
	if (nb < 0)
	{
		string[0] = '-';
		nb = -nb;
	}
	if (nb == 0)
		string[--len] = '0';
	while (nb > 0)
	{
		string[--len] = '0' + (nb % 10);
		nb /= 10;
	}
	return (string);
}
