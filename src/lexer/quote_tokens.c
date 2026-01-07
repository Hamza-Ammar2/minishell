
#include "../../include/minishell.h"
#include "../../libft/libft.h"

/*
** Called from: tokenize() in tokenizer.c
** Purpose: Check if current character is a quote
** Example: is_quote(input[i]) where i is the current position
*/
int	is_quote(char c)
{
	return (c == 34 || c == 39);
}

/*
** Called from: extract_quoted_word() below
** Purpose: Find the index of the matching closing quote
** Parameters:
**   - str: string starting AFTER the opening quote
**   - quote: the quote character to match (' or ")
** Returns: index of closing quote, or -1 if not found
** Example: find_closing_quote(&input[i + 1], '\'')
*/
int	find_closing_quote(const char *str, char quote)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == quote)
			return (i);
		i++;
	}
	return (-1);
}

/*
** Called from: tokenize() in tokenizer.c
** Purpose: Extract a quoted string (with quotes included)
** Parameters:
**   - input: full input string
**   - i: pointer to current position (will be updated)
**   - quote_type: pointer to store 1 (single) or 2 (double)
** Returns: allocated string with quotes, or NULL on error
** Example: extract_quoted_word(input, &i, &quote_type)
*/
char	*extract_quoted_word(const char *input, int *i, int *quote_type)
{
	char	quote;
	int		close_pos;
	char	*string;

	quote = input[*i];
	if (quote == 39)
		*quote_type = QUOTE_SINGLE;
	else
		*quote_type = QUOTE_DOUBLE;
	close_pos = find_closing_quote(&input[*i + 1], quote);
	if (close_pos == -1)
	{
		ft_putstr_fd("minishell: syntax error: unclosed quote\n", 2);
		return (NULL);
	}
	string = ft_substr(input, *i + 1, close_pos);
	if (!string)
		return (NULL);
	*i += close_pos + 2;
	return (string);
}

/*
** Called from: process_quote() below
** Purpose: Concatenate adjacent quoted strings (no space between)
** Example: "hello""world" becomes one token "helloworld"
** Parameters:
**   - word: the first extracted quoted word
**   - input: full input string
**   - i: pointer to current position (will be updated)
** Returns: concatenated string or NULL on error
*/
static char	*concat_adjacent_quotes(char *word, char *input, int *i)
{
	char	*next_word;
	char	*temp;
	int		quote_type;

	while (input[*i] && is_quote(input[*i]))
	{
		quote_type = 0;
		next_word = extract_quoted_word(input, i, &quote_type);
		if (!next_word)
			return (free(word), NULL);
		temp = ft_strjoin(word, next_word);
		free(word);
		free(next_word);
		if (!temp)
			return (NULL);
		word = temp;
	}
	return (word);
}

/*
** Called from: tokenize() in tokenizer.c
** Purpose: Process a quoted token and add it to the token list
** Parameters:
**   - head: pointer to token list head
**   - input: full input string
**   - i: pointer to current position (will be updated)
** Returns: 1 on success, 0 on failure
*/
int	process_quote(t_token **head, char *input, int *i)
{
	char	*word;
	int		quote_type;
	t_token	*token;

	quote_type = 0;
	word = extract_quoted_word(input, i, &quote_type);
	if (!word)
		return (0);
	word = concat_adjacent_quotes(word, input, i);
	if (!word)
		return (0);
	token = new_token(TOKEN_WORD, word, quote_type);
	add_token_to_list(head, token);
	free(word);
	return (1);
}
