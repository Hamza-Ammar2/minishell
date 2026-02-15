/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haammar <haammar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 03:01:35 by lpons             #+#    #+#             */
/*   Updated: 2026/02/15 15:04:22 by haammar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

static void	handle_numeric_exit(char *exit_arg, t_shell *shell, t_command *cmd)
{
	long long	exit_code;

	if (!str_to_long_long(exit_arg, &exit_code))
	{
		ft_fprintf(2, "exit: %s: numeric argument required\n", exit_arg);
		free(exit_arg);
		shell->exit_status = 2;
		exit_nice(shell, cmd, 2);
	}
	free(exit_arg);
	shell->exit_status = (unsigned char)exit_code;
	exit_nice(shell, cmd, (unsigned char)exit_code);
}

static void	handle_exit_error(char *exit_arg, t_shell *shell, int err_type,
		t_command *cmd)
{
	if (err_type == 0)
	{
		ft_fprintf(2, "exit: %s: numeric argument required\n", exit_arg);
		free(exit_arg);
		shell->exit_status = 2;
		exit_nice(shell, cmd, 2);
	}
}

static int	process_exit_args(t_token **args, t_shell *shell, t_command *cmd)
{
	char	*exit_arg;
	char	*trimmed;

	if (!args[1])
		exit(shell->exit_status);
	exit_arg = expand_str(shell, args[1]->value, args[1]->quote_type);
	trimmed = trim_whitespace(exit_arg);
	free(exit_arg);
	if (!trimmed || !is_numeric(trimmed))
		handle_exit_error(trimmed, shell, 0, cmd);
	if (args[2])
	{
		ft_fprintf(2, "exit: too many arguments\n");
		free(trimmed);
		shell->exit_status = 1;
		return (1);
	}
	handle_numeric_exit(trimmed, shell, cmd);
	return (0);
}

int	ft_exit(t_token **args, t_shell *shell, t_command *cmds)
{
	char	*cmd;

	if (!args || !args[0])
		return (-1);
	cmd = expand_str(shell, args[0]->value, args[0]->quote_type);
	if (!cmd)
		return (1);
	if (ft_strcmp(cmd, "exit") != 0)
		return (free(cmd), -1);
	free(cmd);
	if (isatty(STDIN_FILENO))
		ft_fprintf(1, "exit\n");
	return (process_exit_args(args, shell, cmds));
}
