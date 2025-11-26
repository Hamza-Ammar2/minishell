#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

# define PROMPT "minishell$ "

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	char	*input;
	t_env	*env;
	char	**envp;
	int		exit_status;
	int		stdin_backup;
	int		stdout_backup;
}	t_shell;

void	init_shell(t_shell *shell);
void	shell_loop(t_shell *shell);
void	cleanup_shell(t_shell *shell);

#endif
