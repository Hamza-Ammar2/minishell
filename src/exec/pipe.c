/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haammar <haammar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 03:03:24 by lpons             #+#    #+#             */
/*   Updated: 2026/02/19 23:15:11 by haammar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

int	connect_pipes(t_command *cmd, int fd[3][2])
{
	int	i;
	int	failed;

	i = fd[2][0];
	failed = 0;
	if (i > 0)
		failed = dup2(fd[(i + 1) % 2][0], STDIN_FILENO);
	if (failed == -1)
		return (perror("dup2: connecting pipes failed"), -1);
	if (cmd->next)
		failed = dup2(fd[i % 2][1], STDOUT_FILENO);
	if (failed == -1)
		perror("dup2: connecting pipes failed");
	return (failed);
}

int	close_pipes(t_command *cmds, int fd[3][2])
{
	if (fd[2][0] > 0)
	{
		close(fd[(fd[2][0] + 1) % 2][0]);
		close(fd[(fd[2][0] + 1) % 2][1]);
	}
	/* close(fd[(fd[2][0] + 1) % 2][0]);
	close(fd[(fd[2][0] + 1) % 2][1]); */
	if (!cmds->next || fd[2][1] < 0)
	{
		close(fd[fd[2][0] % 2][0]);
		close(fd[fd[2][0] % 2][1]);
		return (1);
	}
	return (0);
}

void	close_child(int fd[3][2])
{
	if (fd[2][0] > 0)
	{
		close(fd[(fd[2][0] + 1) % 2][0]);
		close(fd[(fd[2][0] + 1) % 2][1]);
	}
	close(fd[fd[2][0] % 2][0]);
	close(fd[fd[2][0] % 2][1]);
}
