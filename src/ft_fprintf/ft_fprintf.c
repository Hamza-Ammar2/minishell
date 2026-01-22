/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haammar <haammar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 13:12:44 by haammar           #+#    #+#             */
/*   Updated: 2026/01/22 00:01:25 by haammar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

static int	print_var(int fd, va_list arg_ptr, char type, int *valid);

static int	isvalid(char c)
{
	if (c == 'c' || c == 's' || c == 'p' || c == 'd'
		|| c == 'i' || c == 'u' || c == 'x' || c == 'X'
		|| c == '%')
		return (0);
	return (1);
}

int	ft_fprintf(int fd, const char *s, ...)
{
	va_list	arg_ptr;
	char	*str;
	int		c;
	int		valid;

	if (!s)
		return (-1);
	va_start(arg_ptr, s);
	c = 0;
	valid = 0;
	str = (char *) s;
	while (*str)
	{
		if (*str == '%')
			c += print_var(fd, arg_ptr, *(++str), &valid);
		else
			c += write(fd, str, 1);
		if (*str)
			str++;
	}
	va_end(arg_ptr);
	return (c - (c * valid) - valid);
}

static int	print_var(int fd, va_list arg_ptr, char type, int *valid)
{
	char	c;

	if (!*valid)
		*valid = isvalid(type);
	if (!type)
		return (-1);
	if (type == 'c')
		return (c = va_arg(arg_ptr, int), write(fd, &c, 1));
	if (type == 's')
		return (print_str(fd, (char *) va_arg(arg_ptr, void *)));
	if (type == 'X' || type == 'x')
		return (print_ptr(fd, (unsigned long) va_arg(arg_ptr, unsigned int), type));
	if (type == 'd' || type == 'i')
		return (print_num(fd, (long) va_arg(arg_ptr, int)));
	if (type == 'p')
		return (print_ptr(fd, (unsigned long) va_arg(arg_ptr, void *), type));
	if (type == 'u')
		return (print_num(fd, (long) va_arg(arg_ptr, unsigned int)));
	if (type == '%')
		return (write(fd, "%", 1));
	return (write(fd, "%", 1) + write(fd, &type, 1));
}
