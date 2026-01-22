

#include "../include/minishell.h"
#include "../libft/libft.h"

/*
** 🔧 What the function Does
** Initializes the shell structure with default values.
**
** 🔗 Role in the Program
** Sets up the initial state of the shell before entering the main loop.
**
** 🧩 Step-by-Step
** 1. Set exit status to 0 (success).
*/

static void	fill_join(char *str1, char *str2, char *joined)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str1[i])
	{
		joined[i] = str1[i];
		i++;
	}
	joined[i] = '=';
	i++;
	while (str2[j])
	{
		joined[i + j] = str2[j];
		j++;
	}
	joined[i + j] = '\0';
}

static char	**get_arr(t_env *env, char **envp)
{
	t_env	*current;
	int		i;

	current = env;
	i = 0;
	while (current)
	{
		envp[i] = malloc(sizeof(char) * (ft_strlen(current->key)
					+ ft_strlen(current->value) + 2));
		if (!envp[i])
			return (free_splits(envp), NULL);
		fill_join(current->key, current->value, envp[i]);
		i++;
		current = current->next;
	}
	envp[i] = NULL;
	return (envp);
}

char	**env2arr(t_env *env)
{
	t_env	*current;
	char	**envp;
	int		size;

	size = 0;
	current = env;
	while (current)
	{
		size++;
		current = current->next;
	}
	envp = malloc(sizeof(char *) * (size + 1));
	if (!envp)
		return (NULL);
	return (get_arr(env, envp));
}

void	init_shell(t_shell *shell, char **envp)
{
	shell->exit_status = 0;
	shell->env = NULL;
	export(envp, shell);
	shell->input = NULL;
	shell->envp = envp;
	shell->stdin_backup = dup(STDIN_FILENO);
	shell->stdout_backup = dup(STDOUT_FILENO);
}
