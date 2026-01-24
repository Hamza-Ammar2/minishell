/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directio.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haammar <haammar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 03:01:58 by lpons             #+#    #+#             */
/*   Updated: 2026/01/24 21:04:45 by haammar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

static int	here_doc_app(t_shell *shell, t_token *redir)
{
	int	file;

	if (redir->type == TOKEN_REDIRECT_APPEND)
	{
		if (dup2(shell->stdout_backup, STDOUT_FILENO) == -1)
			return (perror("dup2 failed"), 0);
		file = open(redir->value, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (file == -1)
			return (perror("could not open file"), 0);
		if (dup2(file, STDOUT_FILENO) == -1)
			return (perror("dup2 failed"), close(file), 0);
		close(file);
	}
	else if (redir->type == TOKEN_REDIRECT_HEREDOC)
	{
		if (dup2(shell->stdin_backup, STDIN_FILENO) == -1)
			return (perror("dup2 failed"), 0);
		file = open(redir->value, O_RDONLY, 0644);
		if (dup2(file, STDIN_FILENO) == -1)
			return (perror("dup2 failed"), 0);
		close(file);
		return (1);
	}
	return (1);
}

static int	in_out(t_shell *shell, t_token *redir)
{
	int	file;

	if (redir->type == TOKEN_REDIRECT_IN)
	{
		if (dup2(shell->stdin_backup, STDIN_FILENO) == -1)
			return (perror("dup2 failed"), 0);
		file = open(redir->value, O_RDONLY);
		if (file == -1)
			return (perror("could not open file"), 0);
		if (dup2(file, STDIN_FILENO) == -1)
			return (close(file), perror("dup2 failed"), 0);
		close(file);
	}
	else if (redir->type == TOKEN_REDIRECT_OUT)
	{
		if (dup2(shell->stdout_backup, STDOUT_FILENO) == -1)
			return (perror("dup2 failed"), 0);
		file = open(redir->value, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (file == -1)
			return (perror("could not open file"), 0);
		if (dup2(file, STDOUT_FILENO) == -1)
			return (close(file), perror("dup2 failed"), 0);
		close(file);
	}
	return (1);
}

int	direct_io(t_shell *shell, t_command *cmd)
{
	t_token	*redir;
	char	*raw;

	redir = cmd->redirects;
	while (redir)
	{
		raw = redir->value;
		redir->value = expand_str(shell, raw, redir->quote_type);
		free(raw);
		if (!redir->value)
			return (perror("directio: expansion failed"), 0);
		if (redir->type == TOKEN_REDIRECT_IN
			|| redir->type == TOKEN_REDIRECT_OUT)
		{
			if (!in_out(shell, redir))
				return (perror("direct_io failed"), 0);
			redir = redir->next;
			continue ;
		}
		if (!here_doc_app(shell, redir))
			return (perror("direct_here_app failed"), 0);
		redir = redir->next;
	}
	return (1);
}
