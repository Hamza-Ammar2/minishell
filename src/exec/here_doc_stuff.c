/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_stuff.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haammar <haammar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 03:03:17 by lpons             #+#    #+#             */
/*   Updated: 2026/01/25 00:09:47 by haammar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

extern sig_atomic_t	g_sig;

static int	clean_stuff(t_shell *shell, int fd, char *line)
{
	g_sig = 0;
	restore(shell);
	close(fd);
	free(line);
	return (2);
}

static char	*get_exp(t_shell *shell, char *value, int type)
{
	char	*line;
	char	*raw;

	if (!isatty(STDIN_FILENO))
		raw = get_next_line(STDIN_FILENO);
	else
		raw = readline("> ");
	if (!raw)
		return (NULL);
	if (strcmpy(raw, value) == 0)
		return (free(raw), NULL);
	(void)type;
	(void)shell;
	line = expand_quo(shell, raw, type);
	//line = raw;
	if (g_sig)
	{
		free(raw);
		return (NULL);
	}
	free(raw);
	return (line);
}

static int	here_doc_read(t_shell *shell, char *value, int type, int fd)
{
	char	*line;

	line = get_exp(shell, value, type);
	if (g_sig)
		return (free(value), clean_stuff(shell, fd, line));
	while (strcmpy(line, value) != 0)
	{
		write(fd, line, ft_strlen(line));
		if (isatty(STDIN_FILENO))
			write(fd, "\n", 1);
		free(line);
		line = get_exp(shell, value, type);
		if (g_sig)
			return (free(value), clean_stuff(shell, fd, line));
		if (!line)
			break ;
	}
	if (line)
		free(line);
	return (free(value), close(fd), 1);
}

static int	heredoc(t_shell *shell, t_token *redir)
{
	int		fd;
	char	*delim;

	if (redir->type != TOKEN_REDIRECT_HEREDOC)
		return (1);
	delim = expand_str_hd(shell, redir->value, redir->quote_type);
	if (!delim)
		return (0);
	free(redir->value);
	redir->value = make_hd();
	if (!redir->value)
		return (0);
	fd = open(redir->value, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
		return (0);
	return (here_doc_read(shell, delim, redir->quote_type, fd));
}

int	here_doc(t_shell *shell, t_command *cmds)
{
	t_command *cmd;
	t_token	*redir;

	cmd = cmds;
	while (cmd)
	{
		redir = cmd->redirects;
		while (redir)
		{
			if (!heredoc(shell, redir))
				return (0);
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (1);
}
