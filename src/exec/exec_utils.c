/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haammar <haammar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 03:02:29 by lpons             #+#    #+#             */
/*   Updated: 2026/01/24 21:52:19 by haammar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

int	do_builtin(t_command *cmds, t_shell *shell, int fd[3][2])
{
	int	cb;

	cb = check_builtin(cmds, shell, fd);
	if (cb == 0)
		return (0);
	close_pipes(cmds, fd);
	restore(shell);
	fd[2][0] += 1;
	if (cb == -1)
		fd[2][1] = 1;
	return (cb);
}

int	get_status(int last_pid)
{
	int	status;

	waitpid((pid_t)last_pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (status);
}

int	is_dir(char *path)
{
	struct stat	st;

	if (stat(path, &st) != 0)
	{
		perror("stat");
		return (0);
	}
	return (S_ISDIR(st.st_mode));
}

int	update_(t_command *cmd, t_shell *shell)
{
	t_token	*args;
	char	*str;
	char	*arg;

	args = cmd->args[0];
	if (!args)
		return (1);
	str = expand_str(shell, args->value, args->quote_type);
	if (!str)
		return (shell->exit_status = 1, 1);
	arg = ft_strjoin("_=", str);
	if (!arg)
		return (shell->exit_status = 1, free(str), 1);
	if (!exp_one(shell, arg))
		return (shell->exit_status = 1, free(arg), free(str), 1);
	return (free(arg), free(str), 0);
}

int	exit_exec(char **args, char *str)
{
	struct stat	st;
	char		*cmd;

	st.st_mode = 0;
	cmd = args[0];
	if (!cmd || cmd[0] == '\0')
		(ft_fprintf(2, "command not found\n"), exit(127));
	if (ft_strchr(cmd, '/'))
	{
		if (stat(cmd, &st) != 0)
			(ft_fprintf(2, "No such file or directory\n"), exit(127));
		if (S_ISDIR(st.st_mode))
			(ft_fprintf(2, "Is a directory\n"), exit(126));
		if (access(cmd, X_OK) != 0)
			(ft_fprintf(2, "Permission denied\n"), exit(126));
	}
	if (!str)
		(ft_fprintf(2, "command not found\n"), exit(127));
	if (S_ISDIR(st.st_mode))
		(ft_fprintf(2, "Is a directory\n"), exit(126));
	if (access(str, X_OK) != 0)
		(ft_fprintf(2, "Permission denied\n"), exit(126));
	return (0);
}


