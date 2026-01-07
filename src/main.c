#include "../include/minishell.h"

volatile sig_atomic_t sig = 0;

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
	init_shell(&shell);
	shell.envp = envp;
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
		print_command(cmd);
		exec(cmd, shell);
		free_commands(cmd);
		/* dup2(shell->stdin_backup, STDIN_FILENO);
		dup2(shell->stdout_backup, STDOUT_FILENO); */
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

static void	handle_sig(int s)
{
	sig = s;
}

static int	sig_hook(void)
{
	if (sig) {
		rl_replace_line("", 0);
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_done = 1;
		/* rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		rl_done = 1; */
		return 1;
    }
    return 0;
}

void	shell_loop(t_shell *shell)
{
	char	*input;
	struct sigaction sa;

	sa.sa_handler = handle_sig;
	rl_signal_event_hook = sig_hook;
	if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
	while (1)
	{
		if (isatty(STDIN_FILENO))
			input = readline(PROMPT);
		else
			input = (get_next_line(STDIN_FILENO));
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (*input)
		{
			if (isatty(STDIN_FILENO))
				add_history(input);
			process_input(input, shell);
		}
		free(input);
		sig = 0;
	}
}
