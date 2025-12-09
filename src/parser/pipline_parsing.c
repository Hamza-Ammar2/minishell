#include "../../include/minishell.h"

int count_pipes(t_token *tokens)
{
    int i;

    i = 0;
    while(tokens)
    {
        if(tokens->type == TOKEN_PIPE)
            i ++;
        tokens = tokens->next;
    }
    return i;
}

t_token *find_next_pipe(t_token *tokens)
{
    while(tokens)
    {
        if(tokens->type == TOKEN_PIPE)
            return(tokens);
        tokens = tokens->next;
    }
    return NULL;
}

t_token *extract_command_tokens(t_token **tokens)
{
    t_token *head;
    t_token *copy;

    head = NULL;
    while (*tokens && (*tokens)->type != TOKEN_PIPE)
    {
        copy = new_token((*tokens)->type, (*tokens)->value, (*tokens)->quote_type);
        add_token_to_list(&head, copy);
        *tokens = (*tokens)->next;
    }
    if (*tokens)  // Skip pipe if present
        *tokens = (*tokens)->next;
    return (head);
}

static void	fill_command_args(t_command *cmd, t_token *tokens)
{
	int		i;
	t_token	*tmp;

	i = 0;
	tmp = tokens;
	while (tmp && tmp->type != TOKEN_PIPE)
	{
		if (tmp->type == TOKEN_WORD)
		{
			cmd->args[i] = ft_strdup(tmp->value);
			i++;
		}
		else if (is_operator_token(tmp->type) && tmp->type != TOKEN_PIPE)
		{
			if (tmp->next)
				tmp = tmp->next;
		}
		tmp = tmp->next;
	}
	cmd->args[i] = NULL;
}

static t_command	*create_pipeline_command(t_token *cmd_tokens)
{
	t_command	*cmd;
	int			arg_count;

	cmd = new_command();
	if (!cmd)
		return (NULL);
	arg_count = count_args(cmd_tokens);
	cmd->args = malloc(sizeof(char *) * (arg_count + 1));
	if (!cmd->args)
	{
		free(cmd);
		return (NULL);
	}
	fill_command_args(cmd, cmd_tokens);
	return (cmd);
}

static void	link_command(t_command **head, t_command **current, t_command *new)
{
	if (!*head)
		*head = new;
	else
		(*current)->next = new;
	*current = new;
}

t_command	*parse_pipeline(t_token *tokens)
{
	t_command	*head;
	t_command	*current;
	t_command	*new_cmd;
	t_token		*cmd_tokens;
	t_token		*token_copy;

	head = NULL;
	current = NULL;
	token_copy = tokens;
	while (token_copy)
	{
		cmd_tokens = extract_command_tokens(&token_copy);
		if (!cmd_tokens)
			break ;
		new_cmd = create_pipeline_command(cmd_tokens);
		free_tokens(cmd_tokens);
		if (!new_cmd)
			return (free_commands(head), NULL);
		link_command(&head, &current, new_cmd);
	}
	return (head);
}
