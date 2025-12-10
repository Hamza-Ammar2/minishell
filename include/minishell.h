#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <unistd.h>
# include <errno.h>

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

typedef enum e_quote_type
{
	QUOTE_NONE = 0,
	QUOTE_SINGLE = 1,
	QUOTE_DOUBLE = 2
}	t_quote_type;

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
	char                **args;           // Command and arguments
	t_token             *redirects;       // List of redirect tokens (operator + filename pairs)
	struct s_command    *next;            // Next command in pipeline
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
int				process_quote(t_token **head, char *input, int *i);

/* Parser functions */
t_command		*parse(t_token *tokens);
t_command		*new_command(void);
void			free_commands(t_command *commands);
int				validate_syntax(t_token *tokens);

/* Pipeline parsing functions */
t_command		*parse_pipeline(t_token *tokens);
int				count_pipes(t_token *tokens);

/* Redirection parsing functions */
t_token			*extract_redirections(t_token *tokens);
void			parse_redirections(t_command *cmd, t_token *tokens);

/* Parser utility functions */
int				is_operator_token(t_token_type type);
t_token			*get_last_token(t_token *tokens);
int				count_args(t_token *tokens);

/* Helper functions (will need libft or implement these) */
int				ft_strcmp(const char *s1, const char *s2);
int				ft_isspace(int c);
size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *s);


/* Execution part */
void    exec(t_command *cmds);
char    **get_path(char **paths, char *cmd);
char 	*create_path(char *path, char *cmd);
void    direct_io(t_command *cmd);
#endif
