
#include "../include/minishell.h"

/*
** 🔧 What the function Does
** Frees all allocated resources and cleans up the shell.
**
** 🔗 Role in the Program
** Ensures proper memory cleanup before program termination.
**
** 🧩 Step-by-Step
** 1. Clear readline history.
*/
void	cleanup_shell(t_shell *shell)
{
	close(shell->stdin_backup);
	close(shell->stdout_backup);
	rl_clear_history();
}
