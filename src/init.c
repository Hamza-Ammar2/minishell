

#include "../include/minishell.h"

/*
** 🔧 What the function Does
** Initializes the shell structure with default values.
**
** 🔗 Role in the Program
** Sets up the initial state of the shell before entering the main loop.
**
** 🧩 Step-by-Step
** 1. Set exit status to 0 (success).
*/
void	init_shell(t_shell *shell)
{
	shell->exit_status = 0;
	shell->env = NULL;
	shell->input = NULL;
	shell->envp = NULL;
	shell->stdin_backup = dup(STDIN_FILENO);
	shell->stdout_backup = dup(STDOUT_FILENO);
}
