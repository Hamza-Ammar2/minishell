/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpons <lpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 14:00:00 by lpons             #+#    #+#             */
/*   Updated: 2026/02/14 14:00:00 by lpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"
#include <limits.h>

/*
** FIX: Trim whitespace from string before checking if numeric
** Bash accepts "exit '    4    '" and exits with code 4
** This function removes leading and trailing spaces/tabs
*/
char	*trim_whitespace(char *str)
{
	char	*start;
	char	*end;
	char	*result;
	int		len;

	start = str;
	while (*start == ' ' || *start == '\t')
		start++;
	if (*start == '\0')
		return (ft_strdup(""));
	end = start + ft_strlen(start) - 1;
	while (end > start && (*end == ' ' || *end == '\t'))
		end--;
	len = end - start + 1;
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	ft_strlcpy(result, start, len + 1);
	return (result);
}

int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

/*
** FIX: Use long long instead of int to handle full range of exit codes
** FIX: Detect overflow - bash treats overflow as non-numeric error (exit 2)
** This function converts string to long long and detects overflow
** Returns 1 on success, 0 on overflow/invalid
** Special handling for LLONG_MIN (-9223372036854775808) edge case
*/
int	str_to_long_long(char *str, long long *result)
{
	long long	num;
	int			sign;
	int			i;
	int			digit;

	num = 0;
	sign = 1;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
	{
		digit = str[i] - '0';
		if (sign == 1 && num > (LLONG_MAX - digit) / 10)
			return (0);
		if (sign == -1 && num > (-(LLONG_MIN + digit)) / 10)
			return (0);
		num = num * 10 + digit;
		i++;
	}
	*result = num * sign;
	return (1);
}
