
#include "../include/minishell.h"

void	cleanup_shell(t_shell *shell)
{
	(void)shell;
	rl_clear_history();
}
