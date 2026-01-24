/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpons <lpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 13:15:24 by haammar           #+#    #+#             */
/*   Updated: 2026/01/24 03:00:48 by lpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

static int	func(int fd, long n, char *nums, int base)
{
	int	c;

	c = 0;
	if (n > base - 1)
		c += func(fd, n / base, nums, base);
	return (c + write(fd, &nums[n % base], 1));
}

static int	func_ptr(int fd, unsigned long n, char *nums, int base)
{
	int	c;

	c = 0;
	if (n > (unsigned long)(base - 1))
		c += func_ptr(fd, n / base, nums, base);
	return (c + write(fd, &nums[n % base], 1));
}

int	print_ptr(int fd, unsigned long n, char type)
{
	char	*nums;
	int		c;
	int		base;

	if (type == 'X')
		nums = "0123456789ABCDEF";
	else
		nums = "0123456789abcdef";
	base = 16;
	c = 0;
	if (type == 'p')
	{
		if (!n)
			return (write(fd, "(nil)", 5));
		c += write(fd, "0x", 2);
	}
	return (c + func_ptr(fd, n, nums, base));
}

int	print_num(int fd, long n)
{
	int		base;
	char	*nums;
	int		c;

	nums = "0123456789";
	base = 10;
	c = 0;
	if (n < 0)
	{
		c += write(fd, "-", 1);
		n = -n;
	}
	return (c + func(fd, n, nums, base));
}

int	print_str(int fd, char *s)
{
	size_t	c;

	if (!s)
		return (write(fd, "(null)", 6));
	c = 0;
	while (*s)
	{
		c += write(fd, s, 1);
		s++;
	}
	return (c);
}
