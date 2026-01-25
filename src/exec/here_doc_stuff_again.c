/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_stuff_again.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpons <lpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 01:06:10 by lpons             #+#    #+#             */
/*   Updated: 2026/01/25 14:54:22 by lpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

char	*make_hd(void)
{
	static int	name;
	char		*tmp;
	char		*file;

	tmp = ft_itoa(name);
	if (!tmp)
		return (NULL);
	file = ft_strjoin("/tmp/", tmp);
	if (!file)
		return (free(tmp), NULL);
	free(tmp);
	while (access(file, F_OK) != -1)
	{
		name++;
		tmp = ft_itoa(name);
		if (!tmp)
			return (NULL);
		free(file);
		file = ft_strjoin("/tmp/", tmp);
		if (!file)
			return (NULL);
		free(tmp);
	}
	return (file);
}
