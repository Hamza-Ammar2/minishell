#include "../../include/minishell.h"

/*
** 🔧 What the function Does
** Creates a new token node.
**
** 🔗 Role in the Program
** Helper function for building the token linked list.
**
** 🧩 Step-by-Step
** 1. Allocate memory for token.
** 2. Set token type.
** 3. Duplicate token value.
** 4. Initialize next pointer to NULL.
*/
t_token *new_token(t_token_type type, char *value, int quote_type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	if (value)
	{
		token->value = ft_strdup(value);
		if (!token->value)
			return (free(token), NULL);
	}
	else
		token->value = NULL;
	token->next = NULL;
	token->quote_type = quote_type;
	return (token);
}

/*
** 🔧 What the function Does
** Frees all tokens in the linked list.
**
** 🔗 Role in the Program
** Cleanup function to prevent memory leaks.
**
** 🧩 Step-by-Step
** 1. Traverse token list.
** 2. Free token value string.
** 3. Free token node.
** 4. Move to next token.
*/
void	free_tokens(t_token *tokens)
{
	t_token	*temp;

	while (tokens != NULL)
	{
		temp = tokens->next;
		if (tokens->value)
			free(tokens->value);
		free(tokens);
		tokens = temp;
	}
}

/*
** 🔧 What the function Does
** Adds a token to the end of the token linked list.
**
** 🔗 Role in the Program
** Helper function for building the token list during tokenization.
**
** 🧩 Step-by-Step
** 1. Check if list is empty.
** 2. If empty, set head to new token.
** 3. If not empty, traverse to last node.
** 4. Link new token to end of list.
*/
void	add_token_to_list(t_token **head, t_token *new_token)
{
	t_token	*current;

	if (!new_token)
		return ;
	if (*head == NULL)
	{
		*head = new_token;
		return ;
	}
	current = *head;
	while (current->next != NULL)
		current = current->next;
	current->next = new_token;
}

/*
** 🔧 What the function Does
** Extracts a word from input until space or operator.
**
** 🔗 Role in the Program
** Isolates word tokens from the input string.
**
** 🧩 Step-by-Step
** 1. Count characters until whitespace or operator.
** 2. Allocate string of that length.
** 3. Copy characters into new string.
** 4. Return extracted word.
*/
char	*extract_word(char *input)
{
	int		len;
	char	*word;
	int		i;

	len = 0;
	while (input[len] && !ft_isspace(input[len]) 
		&& !is_operator(&input[len]) && !is_quote(input[len]))
		len++;
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = input[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}
