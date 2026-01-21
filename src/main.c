#include "../include/minishell.h"

extern sig_atomic_t sig;

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
	init_shell(&shell, envp);
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
		return ;
	if (!validate_syntax(tokens))
	{
		free_tokens(tokens);
		return ;
	}
	cmd = parse(tokens);
	if (cmd)
	{
		//print_command(cmd);
		exec(cmd, shell);
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
	int		is_interactive;
	
	is_interactive = isatty(STDIN_FILENO);
	if (!init_sig())
		return ;
	while (1)
	{
		if (is_interactive)
			input = readline(PROMPT);
		else
			input = (get_next_line(STDIN_FILENO));
		if (!input)
		{
			// FIX: Only print "exit" in interactive mode to prevent tester issues
			if (is_interactive)
				printf("exit\n");
			break ;
		}
		if (*input)
		{
			if (is_interactive)
				add_history(input);
			process_input(input, shell);
		}
		free(input);
		sig = 0;
	}
}
