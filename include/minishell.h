#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

# define PROMPT "minishell$ "

/* Lukes Parser Structs */
typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_REDIRECT_APPEND,
	TOKEN_REDIRECT_HEREDOC,
}	t_token_type;

// 2. Token struct
typedef struct s_token
{
    t_token_type    type;
    char            *value;
    struct s_token  *next;
	int 			quote_type;
}   t_token;

// 3. Command struct
typedef struct s_command
{
    char    **args;
}   t_command;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	char	*input;
	t_env	*env;
	char	**envp;
	int		exit_status;
	int		stdin_backup;
	int		stdout_backup;
}	t_shell;

void	init_shell(t_shell *shell);
void	shell_loop(t_shell *shell);
void	cleanup_shell(t_shell *shell);

/* Tokenizer functions */
t_token			*tokenize(char *input);
t_token			*new_token(t_token_type type, char *value, int quote_type);
void			free_tokens(t_token *tokens);
void			add_token_to_list(t_token **head, t_token *new_token);
char			*extract_word(char *input);
char			*is_operator(char *str);
t_token_type	get_token_type(char *op);

/* Quote handling functions */
int				is_quote(char c);
int				find_closing_quote(const char *str, char quote);
char			*extract_quoted_word(const char *input, int *i, int *quote_type);

/* Parser functions */
t_command		*parse(t_token *tokens);
t_command		*new_command(void);
void			free_commands(t_command *commands);
int				validate_syntax(t_token *tokens);

/* Helper functions (will need libft or implement these) */
int				ft_strcmp(const char *s1, const char *s2);
int				ft_isspace(int c);
size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *s);

#endif
