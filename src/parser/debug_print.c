#include "../../include/minishell.h"

/*
** 🔧 What the function Does
** Returns string name for token type.
**
** 🔗 Role in the Program
** Helper for debug printing redirect types.
**
** 🧩 Step-by-Step
** 1. Match token type to string name.
** 2. Return readable operator name.
*/
static const char	*get_redirect_name(t_token_type type)
{
	if (type == TOKEN_REDIRECT_IN)
		return ("<");
	if (type == TOKEN_REDIRECT_OUT)
		return (">");
	if (type == TOKEN_REDIRECT_APPEND)
		return (">>");
	if (type == TOKEN_REDIRECT_HEREDOC)
		return ("<<");
	return ("UNKNOWN");
}

/*
** 🔧 What the function Does
** Prints all redirections for a command.
**
** 🔗 Role in the Program
** Helper to visualize redirect list.
**
** 🧩 Step-by-Step
** 1. Traverse redirect token list.
** 2. Print operator type and filename.
** 3. Show "none" if no redirects.
*/
static void	print_redirects(t_token *redirects)
{
	t_token	*current;

	if (!redirects)
	{
		printf("    redirects: none\n");
		return ;
	}
	current = redirects;
	while (current)
	{
		printf("    redirect: %s '%s'\n", get_redirect_name(current->type),
			current->value);
		current = current->next;
	}
}

/*
** 🔧 What the function Does
** Prints entire command structure for debugging.
**
** 🔗 Role in the Program
** Main debug function to visualize parsed commands.
**
** 🧩 Step-by-Step
** 1. Print command number and args.
** 2. Print redirections if any.
** 3. Indicate if more commands follow.
** 4. Recursively print next command.
*/
void	print_command(t_command *cmd)
{
	static int	cmd_num = 1;
	int			i;

	if (!cmd)
	{
		printf("  (null command)\n");
		return ;
	}
	printf("\nCommand %d:\n", cmd_num++);
	printf("  args: [");
	i = 0;
	while (cmd->args && cmd->args[i])
	{
		// Print value and quote type
		printf("\"%s\" (quote:%d)", 
			cmd->args[i]->value,
			cmd->args[i]->quote_type);
		if (cmd->args[i + 1])
			printf(", ");
		i++;
	}
	printf("]\n");
	print_redirects(cmd->redirects);
	if (cmd->next)
	{
		printf("  next: yes\n");
		print_command(cmd->next);
	}
	else
	{
		printf("  next: no\n");
		cmd_num = 1;
	}
}
