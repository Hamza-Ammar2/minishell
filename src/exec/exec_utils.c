/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haammar <haammar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 03:02:29 by lpons             #+#    #+#             */
/*   Updated: 2026/02/14 07:55:20 by haammar          ###   ########.fr       */
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

	status = 0;
	waitpid((pid_t)last_pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
    	write(2, "Quit (core dumped)\n", 19);
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

	if (!cmd->args)
		return (0);
	args = cmd->args[0];
	if (!args)
		return (0);
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
