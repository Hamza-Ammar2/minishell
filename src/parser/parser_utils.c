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
	cmd->redirects = NULL;
	cmd->next = NULL;
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
	t_command	*next;
	int			i;

	while (commands)
	{
		next = commands->next;
		if (commands->args)
		{
			i = 0;
			while (commands->args[i])
			{
				free_tokens(commands->args[i]);
				i++;
			}
			free(commands->args);
		}
		free_tokens(commands->redirects);
		free(commands);
		commands = next;
	}
}

/*
** 🔧 What the function Does
** Gets the last token in a linked list.
**
** 🔗 Role in the Program
** Utility function for finding the end of a token list.
**
** 🧩 Step-by-Step
** 1. Check if list is empty.
** 2. Traverse to last token.
** 3. Return pointer to last token.
*/
t_token	*get_last_token(t_token *tokens)
{
	if (!tokens)
		return (NULL);
	while (tokens->next)
		tokens = tokens->next;
	return (tokens);
}

