/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haammar <haammar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 02:47:18 by lpons             #+#    #+#             */
/*   Updated: 2026/02/18 02:46:48 by haammar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

extern sig_atomic_t	g_sig;

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	if (!init_sig())
		return (1);
	if (!init_shell(&shell, argv, envp))
		return (1);
	shell_loop(&shell);
	cleanup_shell(&shell);
	return (shell.exit_status);
}

static int	tokenize_input(t_shell *shell, char *input, t_token **out)
{
	*out = tokenize(input);
	if (!*out)
		return (shell->exit_status = 2, 0);
	if (!validate_syntax(*out))
	{
		free_tokens(*out);
		return (shell->exit_status = 2, 0);
	}
	return (1);
}

void	process_input(char *input, t_shell *shell)
{
	t_token		*tokens;
	t_command	*cmd;

	if (!tokenize_input(shell, input, &tokens))
		return ;
	cmd = parse(tokens);
	shell->cur_tokens = tokens;
	if (cmd && here_doc(shell, cmd))
	{
		exec(cmd, shell);
		free_commands(cmd);
	}
	else if (cmd)
		free_commands(cmd);
	free_tokens(tokens);
	shell->cur_tokens = NULL;
}

static void	handle_input(t_shell *shell)
{
	if (isatty(STDIN_FILENO))
		add_history(shell->input);
	process_input(shell->input, shell);
}

void	shell_loop(t_shell *shell)
{
	while (1)
	{
		if (isatty(STDIN_FILENO))
			shell->input = readline(PROMPT);
		else
			shell->input = get_next_line(STDIN_FILENO);
		if (!shell->input)
		{
			if (isatty(STDIN_FILENO))
				printf("exit\n");
			break ;
		}
		if (*shell->input)
			handle_input(shell);
		if (g_sig)
			shell->exit_status = 130;
		free(shell->input);
		shell->input = NULL;
		g_sig = 0;
	}
}
