#include "../include/minishell.h"

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

void	shell_loop(t_shell *shell)
{
	char	*input;

	(void)shell;
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
			printf("You typed: %s\n", input);
		}
		free(input);
	}
}
