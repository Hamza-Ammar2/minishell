/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpons <lpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 01:06:27 by lpons             #+#    #+#             */
/*   Updated: 2026/01/25 14:53:57 by lpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

void	exit_nice(t_shell *shell, t_command *cmd, int stat)
{
	free_commands(cmd);
	cleanup_shell(shell);
	exit(stat);
}

static void	ex1(t_shell *shell, t_command *cmds, char **args)
{
	struct stat	st;
	char		*cmd;

	st.st_mode = 0;
	cmd = args[0];
	if (ft_strchr(cmd, '/'))
	{
		if (stat(cmd, &st) != 0)
			(free_splits(args), ft_fprintf(2, "No such file or directory\n"),
				exit_nice(shell, cmds, 127));
		if (S_ISDIR(st.st_mode))
			(free_splits(args), ft_fprintf(2, "Is a directory\n"),
				exit_nice(shell, cmds, 126));
		if (access(cmd, X_OK) != 0)
			(free_splits(args), ft_fprintf(2, "Permission denied\n"),
				exit_nice(shell, cmds, 126));
	}
}

/* LEAK FIX: Free str (path) in all error exit paths.
** Previously str was allocated by get_path() but never freed when
** exit_exec detected an error and called exit_nice.
** Note: Only free str if it was allocated separately (str != args[0]).
** When cmd contains '/' and exists, get_path returns args[0] directly. */
int	exit_exec(t_shell *shell, t_command *cmds, char **args, char *str)
{
	struct stat	st;
	char		*cmd;

	st.st_mode = 0;
	cmd = args[0];
	if (!cmd || cmd[0] == '\0')
		(free_splits(args), ft_fprintf(2, "command not found\n"),
			exit_nice(shell, cmds, 127));
	ex1(shell, cmds, args);
	if (!str)
		(free_splits(args), ft_fprintf(2, "command not found\n"),
			exit_nice(shell, cmds, 127));
	if (S_ISDIR(st.st_mode))
	{
		if (str != cmd)
			free(str);
		(free_splits(args), ft_fprintf(2, "Is a directory\n"),
			exit_nice(shell, cmds, 126));
	}
	if (access(str, X_OK) != 0)
	{
		if (str != cmd)
			free(str);
		(free_splits(args), ft_fprintf(2, "Permission denied\n"),
			exit_nice(shell, cmds, 126));
	}
	return (0);
}
