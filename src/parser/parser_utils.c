#include "../../include/minishell.h"

/*
** 🔧 What the function Does
** Creates a new command node.
**
** 🔗 Role in the Program
** Helper for building command linked list during parsing.
**
** 🧩 Step-by-Step
** 1. Allocate memory for command.
** 2. Initialize all fields to NULL/0.
** 3. Return new command node.
*/
t_command	*new_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	return (cmd);
}

/*
** 🔧 What the function Does
** Frees all commands in the linked list.
**
** 🔗 Role in the Program
** Cleanup function to prevent memory leaks.
**
** 🧩 Step-by-Step
** 1. Free command arguments array.
** 2. Free redirections.
** 3. Free command node.
** 4. Move to next command.
*/
void	free_commands(t_command *commands)
{
	int		i;

	if (!commands)
		return ;
	if (commands->args)
	{
		i = 0;
		while (commands->args[i])
		{
			free(commands->args[i]);
			i++;
		}
		free(commands->args);
	}
	free(commands);
}
