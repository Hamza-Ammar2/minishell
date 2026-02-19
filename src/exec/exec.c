/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haammar <haammar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 03:02:38 by lpons             #+#    #+#             */
/*   Updated: 2026/02/19 23:21:03 by haammar          ###   ########.fr       */
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
			return (/* close(fd[1][1]), close(fd[1][0]), */
				perror("could not update _"), 1);
		if (ft_exit(cmds->args, shell, cmds) == 1)
			return (/* close(fd[1][1]), close(fd[1][0]), */ shell->exit_status = 1,
				1);
		if (check_builtin(cmds, shell, fd) != 0)
			return (restore(shell), /* close(fd[1][1]), close(fd[1][0]), */
				/* shell->exit_status = fd[2][1],  */1);
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
	fd[2][0] = 0;
	fd[2][1] = 1;
	if (check_begin(cmds, shell, fd))
		return ;
	/* if (pipe(fd[1]) == -1)
		return (perror("pipe failed")); */
	paths = get_paths(shell);
	last_pid = rec_exec(paths, fd, cmds, shell);
	shell->exit_status = last_pid;
	if (last_pid != 1 && last_pid != -1 && last_pid != 0)
		shell->exit_status = get_status(last_pid);
	while (wait(NULL) > 0)
		;
	free_splits(paths);
	if (!init_sig())
		return (shell->exit_status = 1, (void)0);
}

static char	**dumb_exit(t_command *cmd, t_shell *shell, char **paths)
{
	char	**args;

	args = wraper(cmd->args, shell);
	if (!args)
		(free_splits(paths), exit_nice(shell, cmd, 1));
	if (ft_strcmp(args[0], "exit") == 0)
	{
		free_splits(args);
		free_splits(paths);
		ft_exit(cmd->args, shell, cmd);
	}
	return (args);
}

static void	exec_single(t_command *cmd, t_shell *shell, int fd[3][2],
		char **paths)
{
	char	*str;
	char	**args;
	char	**envp;

	/* LEAK FIX: Free paths before exit_nice in all child exit paths.
	** Child processes inherit paths array but never freed it, causing
	** ~1,325 bytes leak per forked command. */
	if (do_builtin(cmd, shell, fd) != 0)
		(/* close_child(fd), */ free_splits(paths), exit_nice(shell, cmd, shell->exit_status));
	if (connect_pipes(cmd, fd) == -1)
		(close_child(fd), free_splits(paths), exit_nice(shell, cmd, 1));
	if (!direct_io(shell, cmd))
		(close_child(fd), free_splits(paths), exit_nice(shell, cmd, 1));
	if (!cmd->args || !cmd->args[0])
		(close_child(fd), free_splits(paths), exit_nice(shell, cmd, 0));
	close_child(fd);
	args = dumb_exit(cmd, shell, paths);
	str = get_path(paths, args[0]);
	/* LEAK FIX: Free paths before exit_exec since it may call exit_nice */
	free_splits(paths);
	exit_exec(shell, cmd, args, str);
	/* LEAK FIX: Store env2arr result to free on execve failure */
	envp = env2arr(shell->env);
	execve(str, args, envp);
	/* LEAK FIX: Free envp and args on execve failure.
	** Only free str if it was separately allocated (str != args[0]).
	** When cmd contains '/' and exists, get_path returns args[0] directly. */
	free_splits(envp);
	if (str != args[0])
		free(str);
	free_splits(args);
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
	{
		child_signal();
		exec_single(cmds, shell, fd, paths);
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	restore(shell);
	if (close_pipes(cmds, fd))
		return (fd[2][1]);
	return (fd[2][0] += 1, rec_exec(paths, fd, cmds->next, shell));
}
