
#include "../../include/minishell.h"
#include "../../libft/libft.h"

/*
** Called from: tokenize() in tokenizer.c
** Purpose: Check if current character is a quote
** Example: is_quote(input[i]) where i is the current position
*/
int is_quote(char c)
{
    return(c == 34 || c == 39);
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
int find_closing_quote(const char *str, char quote)
{
    int i;

    i = 0;
    while(str[i])
    {
        if(str[i] == quote)
            return i;
        i ++;
    }
    return(-1);
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
char *extract_quoted_word(const char *input, int *i, int *quote_type)
{
    char    quote;
    int     close_pos;
    char    *string;
    
    quote = input[*i];
    if (quote == 39)
        *quote_type = 1;
    else
        *quote_type = 2;
    close_pos = find_closing_quote(&input[*i + 1], quote);
    if (close_pos == -1)
    {
        printf("minishell: syntax error: unclosed quote\n");
        return (NULL);
    }
    string = ft_substr(input, *i, close_pos + 2);
    if (!string)
        return (NULL);
    *i = *i + close_pos + 2;
    return (string);
}
