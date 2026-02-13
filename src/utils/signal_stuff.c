/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_stuff.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haammar <haammar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 02:47:21 by lpons             #+#    #+#             */
/*   Updated: 2026/02/13 19:11:08 by haammar          ###   ########.fr       */
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
		if (ioctl(STDIN_FILENO, TIOCSTI, "\n") == -1)
			ft_fprintf(2, "oioctl error\n");
		rl_replace_line("", 0);
		rl_done = 1;
		return (1);
	}
	return (0);
}

int	init_sig(void)
{
	struct sigaction	sa;
	struct sigaction	sa2;

	ft_memset(&sa, 0, sizeof(sa));
	ft_memset(&sa2, 0, sizeof(sa2));
	sa.sa_handler = handle_sig;
	sa2.sa_handler = SIG_IGN;
	rl_signal_event_hook = sig_hook;
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("sigaction");
		return (0);
	}
	if (sigaction(SIGQUIT, &sa2, NULL) == -1)
	{
		perror("sigaction");
		return (0);
	}
	return (1);
}
