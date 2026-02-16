/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haammar <haammar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 02:47:18 by lpons             #+#    #+#             */
/*   Updated: 2026/02/13 23:35:04 by haammar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

extern sig_atomic_t	g_sig;

/*
** 🔧 What the function Does
** Entry point of the minishell program.
**
** 🔗 Role in the Program
** Initializes the shell, runs the main loop, and cleans up
** resources before exit.
**
** 🧩 Step-by-Step
** 1. Initialize shell structure.
** 2. Enter main shell loop.
** 3. Cleanup allocated resources.
** 4. Return exit status.
*/
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

/*
** 🔧 What the function Does
** Processes user input: tokenize, parse, and execute.
**
** 🔗 Role in the Program
** Handles the parsing pipeline for a single command.
**
** 🧩 Step-by-Step
** 1. Tokenize input string.
** 2. Parse tokens into command structure.
** 3. Execute command (TODO).
** 4. Free allocated resources.
*/

void	process_input(char *input, t_shell *shell)
{
	t_token		*tokens;
	t_command	*cmd;

	tokens = tokenize(input);
	if (!tokens)
	{
		shell->exit_status = 2;
		return ;
	}
	if (!validate_syntax(tokens))
	{
		free_tokens(tokens);
		shell->exit_status = 2;
		return ;
	}
	/* WORD SPLITTING: Expand variables and split unquoted expansions.
	** This implements the Tokenize -> Expand -> Re-tokenize pattern.
	** Unquoted $VAR with spaces becomes multiple tokens.
	** Quoted "$VAR" stays as single token (no splitting). */
	tokens = expand_and_split_tokens(shell, tokens);
	if (!tokens)
	{
		shell->exit_status = 1;
		return ;
	}
	cmd = parse(tokens);
	if (cmd && here_doc(shell, cmd))
	{
		exec(cmd, shell);
		free_commands(cmd);
	}
	else if (cmd)
		free_commands(cmd);
	free_tokens(tokens);
}

/*
** 🔧 What the function Does
** Runs the main interactive loop of the shell.
**
** 🔗 Role in the Program
** Continuously reads user input and delegates processing.
**
** 🧩 Step-by-Step
** 1. Display prompt and read input.
** 2. Check for EOF (Ctrl+D).
** 3. Add non-empty input to history.
** 4. Process the input.
** 5. Free input and repeat.
*/

void	shell_loop(t_shell *shell)
{
	char	*input;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			input = readline(PROMPT);
		else
			input = get_next_line(STDIN_FILENO);
		if (!input)
		{
			if (isatty(STDIN_FILENO))
				printf("exit\n");
			break ;
		}
		if (*input)
		{
			if (isatty(STDIN_FILENO))
				add_history(input);
			process_input(input, shell);
		}
		if (g_sig)
			shell->exit_status = 130;
		free(input);
		g_sig = 0;
	}
}
