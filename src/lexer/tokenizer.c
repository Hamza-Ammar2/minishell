#include "../../include/minishell.h"

/*
** 🔧 What the function Does
** Checks if character is an operator and returns operator string.
**
** 🔗 Role in the Program
** Helper to identify operator tokens during tokenization.
**
** 🧩 Step-by-Step
** 1. Check for pipe (|).
** 2. Check for heredoc (<<).
** 3. Check for input redirection (<).
** 4. Check for append (>>).
** 5. Check for output redirection (>).
*/
char	*is_operator(char *str)
{
	if (*str == '|')
		return ("|");
	if (*str == '<' && *(str + 1) == '<')
		return ("<<");
	if (*str == '<')
		return ("<");
	if (*str == '>' && *(str + 1) == '>')
		return (">>");
	if (*str == '>')
		return (">");
	return (NULL);
}

/*
** 🔧 What the function Does
** Determines token type from operator string.
**
** 🔗 Role in the Program
** Maps operator strings to their corresponding token types.
**
** 🧩 Step-by-Step
** 1. Compare operator string.
** 2. Return matching token type.
*/
t_token_type	get_token_type(char *op)
{
	if (ft_strcmp(op, "|") == 0)
		return (TOKEN_PIPE);
	if (ft_strcmp(op, "<") == 0)
		return (TOKEN_REDIRECT_IN);
	if (ft_strcmp(op, ">") == 0)
		return (TOKEN_REDIRECT_OUT);
	if (ft_strcmp(op, ">>") == 0)
		return (TOKEN_REDIRECT_APPEND);
	if (ft_strcmp(op, "<<") == 0)
		return (TOKEN_REDIRECT_HEREDOC);
	return (TOKEN_WORD);
}

/*
** 🔧 What the function Does
** Processes and adds an operator token to the list.
**
** 🔗 Role in the Program
** Helper to handle operator tokens during tokenization.
**
** 🧩 Step-by-Step
** 1. Get token type for operator.
** 2. Create operator token.
** 3. Add to token list.
** 4. Return operator length.
*/
static int	process_operator(t_token **head, char *operator)
{
	t_token	*token;

	token = new_token(get_token_type(operator), NULL, 0);
	add_token_to_list(head, token);
	return (ft_strlen(operator));
}

/*
** 🔧 What the function Does
** Processes and adds a complete word token to the list.
** Handles adjacent quoted/unquoted parts as a single word.
**
** 🔗 Role in the Program
** Helper to handle word tokens during tokenization.
**
** 🧩 Step-by-Step
** 1. Extract complete word (all adjacent parts).
** 2. Create word token with quote type.
** 3. Add to token list.
** 4. Free temporary word.
*/
static int	process_complete_word(t_token **head, char *input, int *i)
{
	t_token	*token;
	char	*word;
	int		quote_type;

	word = extract_complete_word(input, i, &quote_type);
	if (!word)
		return (0);
	token = new_token(TOKEN_WORD, word, quote_type);
	add_token_to_list(head, token);
	free(word);
	return (1);
}

/*
** 🔧 What the function Does
** Converts raw input string into a linked list of tokens.
**
** 🔗 Role in the Program
** First step in processing user input - breaks it into manageable pieces.
**
** 🧩 Step-by-Step
** 1. Skip leading whitespace.
** 2. Identify token type (word, operator, pipe).
** 3. Extract token value.
** 4. Create token node and add to list.
** 5. Repeat until end of input.
*/
t_token	*tokenize(char *input)
{
	t_token	*head;
	char	*operator;
	int		i;

	head = NULL;
	i = 0;
	while (input[i])
	{
		while (input[i] && ft_isspace(input[i]))
			i++;
		if (!input[i])
			break ;
		operator = is_operator(&input[i]);
		if (operator)
		{
			i += process_operator(&head, operator);
		}
		else
		{
			if (!process_complete_word(&head, input, &i))
				return (free_tokens(head), NULL);
		}
	}
	return (head);
}
