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
** Processes and adds a word token to the list.
**
** 🔗 Role in the Program
** Helper to handle word tokens during tokenization.
**
** 🧩 Step-by-Step
** 1. Extract word from input.
** 2. Create word token.
** 3. Add to token list.
** 4. Free temporary word and return length.
*/
static int	process_word(t_token **head, char *input)
{
	t_token	*token;
	char	*word;
	int		len;

	word = extract_word(input);
	if (!word)
		return (0);
	token = new_token(TOKEN_WORD, word, 0);
	add_token_to_list(head, token);
	len = ft_strlen(word);
	free(word);
	return (len);
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
		if (is_quote(input[i]))
		{
			if (!process_quote(&head, input, &i))
				return (free_tokens(head), NULL);
			continue ;
		}
		operator = is_operator(&input[i]);
		if (operator)
			i += process_operator(&head, operator);
		else
			i += process_word(&head, &input[i]);
	}
	return (head);
}
