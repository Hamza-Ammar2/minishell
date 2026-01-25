/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpons <lpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 03:02:38 by lpons             #+#    #+#             */
/*   Updated: 2026/01/25 01:02:59 by lpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

static int	rec_exec(char **paths, int fd[3][2], t_command *cmds,
				t_shell *shell);
static void	exec_single(t_command *cmd, t_shell *shell, int fd[3][2],
				char **paths);

static int	check_begin(t_command *cmds, t_shell *shell, int fd[3][2])
{
	if (!cmds->next)
	{
		if (update_(cmds, shell) != 0)
			return (close(fd[1][1]), close(fd[1][0]), perror("could not update _"), 1);
		if (ft_exit(cmds->args, shell, cmds) == 1)
			return (close(fd[1][1]), close(fd[1][0]), shell->exit_status = 1,
				1);
		if (check_builtin(cmds, shell, fd) != 0)
			return (restore(shell), close(fd[1][1]), close(fd[1][0]),
				shell->exit_status = fd[2][1], 1);
	}
	return (0);
}

void	exec(t_command *cmds, t_shell *shell)
{
	int		fd[3][2];
	char	**paths;
	int		last_pid;

	if (!cmds)
		return ;
	if (pipe(fd[1]) == -1)
		return (perror("pipe failed"));
	fd[2][0] = 0;
	fd[2][1] = 0;
	if (check_begin(cmds, shell, fd))
		return ;
	paths = get_paths(shell);
	last_pid = rec_exec(paths, fd, cmds, shell);
	shell->exit_status = last_pid;
	//printf("%d\n\n\n\n", shell->exit_status);
	if (last_pid != 1 && last_pid != -1 && last_pid != 0)
		shell->exit_status = get_status(last_pid);
	//printf("%d", shell->exit_status);
	while (wait(NULL) > 0)
		;
	free_splits(paths);
}

static void	close_child(int fd[3][2])
{
	int	i;

	i = fd[2][0];
	close(fd[(i + 1) % 2][0]);
	close(fd[(i + 1) % 2][1]);
	close(fd[i % 2][0]);
	close(fd[i % 2][1]);
}

static void	exec_single(t_command *cmd, t_shell *shell, int fd[3][2],
		char **paths)
{
	char	*str;
	char	**args;

	if (do_builtin(cmd, shell, fd) != 0)
		(close_child(fd), exit_nice(shell, cmd, fd[2][1]));
	if (connect_pipes(cmd, fd) == -1)
		(close_child(fd), exit_nice(shell, cmd, 1));
	if (!direct_io(shell, cmd))
		(close_child(fd), exit_nice(shell, cmd, 1));
	if (!cmd->args || !cmd->args[0])
		exit_nice(shell, cmd, 0);
	args = wraper(cmd->args, shell);
	if (!args)
		(close_child(fd), exit_nice(shell, cmd, 1));
	close_child(fd);
	ft_exit(cmd->args, shell, cmd);
	str = get_path(paths, args[0]);
	exit_exec(shell, cmd, args, str);
	close(shell->stdout_backup);
	close(shell->stdin_backup);
	execve(str, args, env2arr(shell->env));
	perror("execve failed");
	exit_nice(shell, cmd, 1);
}

static int	rec_exec(char **paths, int fd[3][2], t_command *cmds,
		t_shell *shell)
{
	if (!cmds)
		return (fd[2][1]);
	if (pipe(fd[fd[2][0] % 2]) == -1)
		return (fd[2][1] = -1, close_pipes(cmds, fd), perror("pipe failed"), 1);
	if (update_(cmds, shell) != 0)
		return (perror("could not update _"), close_pipes(cmds, fd), 1);
	fd[2][1] = fork();
	if (fd[2][1] < 0)
		return (close_pipes(cmds, fd), perror("fork failed"), 1);
	if (fd[2][1] == 0)
		exec_single(cmds, shell, fd, paths);
	restore(shell);
	if (close_pipes(cmds, fd))
		return (fd[2][1]);
	return (fd[2][0] += 1, rec_exec(paths, fd, cmds->next, shell));
}
