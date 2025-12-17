/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haammar <haammar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 20:39:11 by haammar           #+#    #+#             */
/*   Updated: 2025/12/16 20:16:29 by haammar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

static char	*iterread(int fd, char *buff, size_t *start, size_t *end)
{
	size_t	l;
	size_t	duplen;
	char	*s;
	char	*dup;

	duplen = *end - *start;
	dup = 0;
	if (*end > *start)
		dup = append(0, buff + *start, 0, *end - *start);
	if (*end > *start && !dup)
		return (0);
	while (1)
	{
		l = read(fd, buff, BUFFER_SIZE);
		if (!l)
			return (*end = 0, dup);
		s = find_char(buff, '\n', l);
		if (s)
			return (*start = 1 + (size_t)(s - buff),
				*end = l, append(dup, buff, duplen, *start));
		dup = append(dup, buff, duplen, l);
		if (!dup)
			return (0);
		duplen += l;
	}
}

char	*get_next_line(int fd)
{
	static char		buff[BUFFER_SIZE];
	static size_t	start;
	static size_t	end;
	char			*dup;
	char			*s;

	dup = 0;
	if (end > start)
	{
		s = find_char(buff + start, '\n', end - start);
		if (s)
		{
			dup = append(0, buff + start, 0, (size_t)(s - (buff + start)) + 1);
			start = 1 + (size_t)(s - buff);
			return (dup);
		}
	}
	return (iterread(fd, buff, &start, &end));
}
