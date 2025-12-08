#include "../include/minishell.h"

/*
** 🔧 What the function Does
** Entry point of the minishell program.
**
** 🔗 Role in the Program
** Initializes the shell, runs the main loop, and cleans up resources before exit.
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
	(void)envp;
	init_shell(&shell);
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

	(void)shell;
	tokens = tokenize(input);
	if (!tokens)
		return ;
	if (!validate_syntax(tokens))
	{
		free_tokens(tokens);
		return ;
	}
	cmd = parse(tokens);
	if (cmd)
	{
		// Hamza executres here
		printf("Command: %s\n", cmd->args[0]);
		free_commands(cmd);
	}
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
		input = readline(PROMPT);
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (*input)
		{
			add_history(input);
			process_input(input, shell);
		}
		free(input);
	}
}
