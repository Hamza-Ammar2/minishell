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
# include <signal.h>
# include <sys/ioctl.h>
# include <sys/stat.h>

# define PROMPT "minishell$ "
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

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
	t_token				**args;          // Array of pointers to token structs (command and arguments)
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

int		init_shell(t_shell *shell, char **argv, char **envp);
int		init_lvl(t_shell *shell);
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
char			*extract_complete_word(const char *input, int *i, int *quote_type);

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
int				is_redirect_type(t_token_type type);
t_token			*get_last_token(t_token *tokens);
int				count_args(t_token *tokens);

/* Debug functions */
void			print_command(t_command *cmd);

/* Helper functions (will need libft or implement these) */
int				ft_strcmp(const char *s1, const char *s2);
int				ft_isspace(int c);
size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *s);


/* Execution part */
char	**get_paths(t_shell *shell);
char    *get_path(char **paths, char *cmd);
void    exec(t_command *cmds, t_shell *shell);
char 	*create_path(char *path, char *cmd);
int	    direct_io(t_shell *shell, t_command *cmd, int fd[3][2]);
char 	**wraper(t_token **args, t_shell *shell);
void	free_splits(char **splits);
int    	connect_pipes(t_command *cmd, int fd[3][2]);
int  close_pipes(t_command *cmds, int fd[3][2]);
int    restore(t_shell *shell);

/* Utils */
int     get_status(int last_pid);
int    here_doc(t_shell *shell, t_token *redir, int fd[3][2]);
int exit_exec(char **args, char *str);

/* Built-in functions */
int 	do_builtin(t_command *cmds, t_shell *shell, int fd[3][2]);
int     check_builtin(t_command *cmds, t_shell *shell, int fd[3][2]);
int    export(char **args, t_shell *shell);
int    cd(char **args, t_shell *shell);
int	   env(char **args, t_shell *shell);
int    echo(char **args, t_shell *shell);
int    unset(t_shell *shell, char **args);
int    pwd(char **args);
int    ft_exit(t_token **args, t_shell *shell);
int 	is_dir(char *path);

/* Signal handling */
void	handle_sig(int s);
int		sig_hook(void);
int 	init_sig(void);

/* Environment part */
char	**env2arr(t_env *env);
int 	exp_one(t_shell *shell, char *arg);
int    add_env(t_shell *shell, char *key, char *value);
t_env   *find_env(t_shell *shell, char *key);
char 	*do_env(t_shell *shell, char *str);
char    *expand_str(t_shell *shell, char *str, int quote_type);
char    *expand_quo(t_shell *shell, char *str, int quote_type);
char    *expand_str_hd(t_shell *shell, char *str, int quote_type);
void	free_env(t_env *env);
int	update_(t_command *cmd, t_shell *shell);


/* Get Next Line */
char	*get_next_line(int fd);
char	*find_char(char *s, char c, size_t len);
char	*append(char *s1, char *s2, size_t l1, size_t l2);

/* ft_fprintf */
int		print_ptr(int fd, unsigned long ptr, char type);
int		print_num(int fd, long n);
int		print_str(int fd, char *s);
int		ft_fprintf(int fd, const char *s, ...);
#endif
