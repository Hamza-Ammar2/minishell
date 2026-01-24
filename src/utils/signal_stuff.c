/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_stuff.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpons <lpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 02:47:21 by lpons             #+#    #+#             */
/*   Updated: 2026/01/24 02:53:21 by lpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

volatile sig_atomic_t	g_sig = 0;

void	handle_sig(int s)
{
	g_sig = s;
}

int	sig_hook(void)
{
	if (g_sig)
	{
		rl_replace_line("", 0);
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_done = 1;
		return (1);
	}
	return (0);
}

int	init_sig(void)
{
	struct sigaction	sa;

	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = handle_sig;
	rl_signal_event_hook = sig_hook;
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("sigaction");
		return (0);
	}
	return (1);
}
