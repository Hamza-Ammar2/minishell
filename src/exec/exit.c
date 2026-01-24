

#include "../include/minishell.h"
#include "../libft/libft.h"

void    exit_nice(t_shell *shell, t_command *cmd, int stat)
{
    
}

static void ex1(t_shell *shell, t_command *cmds, char **args)
{
    struct stat	st;
	char		*cmd;

	st.st_mode = 0;
	cmd = args[0];
    if (ft_strchr(cmd, '/'))
	{
		if (stat(cmd, &st) != 0)
			(free_splits(args), ft_fprintf(2, "No such file or directory\n"), exit_nice(shell, cmds, 127));
		if (S_ISDIR(st.st_mode))
			(free_splits(args), ft_fprintf(2, "Is a directory\n"), exit_nice(shell, cmds, 126));
		if (access(cmd, X_OK) != 0)
			(free_splits(args), ft_fprintf(2, "Permission denied\n"), exit_nice(shell, cmds, 126));
	}
}

int	exit_exec(t_shell *shell, t_command *cmds, char **args, char *str)
{
	struct stat	st;
	char		*cmd;

	st.st_mode = 0;
	cmd = args[0];
	if (!cmd || cmd[0] == '\0')
		(free_splits(args), ft_fprintf(2, "command not found\n"), exit_nice(shell, cmds, 127));
	ex1(shell, cmds, args);
	if (!str)
		(free_splits(args), ft_fprintf(2, "command not found\n"), exit_nice(shell, cmds, 127));
	if (S_ISDIR(st.st_mode))
		(free_splits(args), ft_fprintf(2, "Is a directory\n"), exit_nice(shell, cmds, 126));
	if (access(str, X_OK) != 0)
		(free_splits(args), ft_fprintf(2, "Permission denied\n"), exit_nice(shell, cmds, 126));
	return (0);
}
