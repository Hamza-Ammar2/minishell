/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_stuff.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haammar <haammar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 02:47:21 by lpons             #+#    #+#             */
/*   Updated: 2026/02/07 08:21:47 by haammar          ###   ########.fr       */
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
	struct sigaction	sa2;

	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = handle_sig;
	sa.sa_handler = SIG_IGN;
	rl_signal_event_hook = sig_hook;
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("sigaction");
		return (0);
	}
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
	{
		perror("sigaction");
		return (0);
	}
	return (1);
}
