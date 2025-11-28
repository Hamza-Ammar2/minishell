#include "../../include/minishell.h"

/*
** 🔧 What the function Does
** Counts the number of WORD tokens in sequence.
**
** 🔗 Role in the Program
** Helper to determine args array size during parsing.
**
** 🧩 Step-by-Step
** 1. Traverse token list.
** 2. Count consecutive TOKEN_WORD tokens.
** 3. Stop at first non-WORD token or end.
*/
static int	count_args(t_token *tokens)
{
	int		count;
	t_token	*current;

	count = 0;
	current = tokens;
	while (current && current->type == TOKEN_WORD)
	{
		count++;
		current = current->next;
	}
	return (count);
}

/*
** 🔧 What the function Does
** Fills the args array with token values.
**
** 🔗 Role in the Program
** Extracts WORD token values into command args array.
**
** 🧩 Step-by-Step
** 1. Traverse token list.
** 2. Copy each WORD token value to args array.
** 3. NULL-terminate the array.
*/
static void	fill_args(t_command *cmd, t_token *tokens)
{
	int		i;
	t_token	*current;

	i = 0;
	current = tokens;
	while (current && current->type == TOKEN_WORD)
	{
		cmd->args[i] = ft_strdup(current->value);
		i++;
		current = current->next;
	}
	cmd->args[i] = NULL;
}

/*
** 🔧 What the function Does
** Converts token list into command structure.
**
** 🔗 Role in the Program
** Organizes tokens into executable commands with arguments and redirections.
**
** 🧩 Step-by-Step
** 1. Validate token sequence.
** 2. Create new command structure.
** 3. Count and allocate args array.
** 4. Fill args array with token values.
** 5. Return parsed command structure.
*/
t_command	*parse(t_token *tokens)
{
	t_command	*cmd;
	int			arg_count;

	if (!tokens)
		return (NULL);
	cmd = new_command();
	if (!cmd)
		return (NULL);
	arg_count = count_args(tokens);
	cmd->args = malloc(sizeof(char *) * (arg_count + 1));
	if (!cmd->args)
	{
		free(cmd);
		return (NULL);
	}
	fill_args(cmd, tokens);
	return (cmd);
}
