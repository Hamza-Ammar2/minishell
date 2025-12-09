#include "../../include/minishell.h"

int count_pipes(t_token *tokens)
{
    int i;

    i = 0;
    while(tokens)
    {
        if(tokens->type == TOKEN_PIPE)
            i ++;
        tokens->next;
    }
    return i;
}

t_token *find_next_pipe(t_token *tokens)
{
    while(tokens)
    {
        if(tokens->type == TOKEN_PIPE)
            return(tokens);
        tokens->next;

    }
}