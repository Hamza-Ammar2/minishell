/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closing_fds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorth <aorth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:04:23 by aorth             #+#    #+#             */
/*   Updated: 2025/06/30 14:16:04 by aorth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_closing_fds(t_cmd *cmd)
{
	if (cmd->fd)
		close(cmd->fd);
	if (cmd->fd_in)
		close(cmd->fd_in);
	if (cmd->fd)
		close(cmd->fd_out);
}
