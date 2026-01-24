/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_func_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haammar <haammar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 03:02:21 by lpons             #+#    #+#             */
/*   Updated: 2026/01/24 20:44:00 by haammar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

static int	pce(t_command *cmds, t_shell *shell, int fd[3][2], char **args)
{
	if (!(ft_strcmp(args[0], "pwd") == 0 || ft_strcmp(args[0], "cd") == 0
			|| ft_strcmp(args[0], "export") == 0))
		return (0);
	if (connect_pipes(cmds, fd) == -1)
		return (-1);
	if (!direct_io(shell, cmds))
		return (-1);
	if (ft_strcmp(args[0], "pwd") == 0)
		fd[2][1] = pwd(&args[1]);
	else if (ft_strcmp(args[0], "cd") == 0)
		fd[2][1] = cd(&args[1], shell);
	else
		fd[2][1] = export(&args[1], shell);
	return (1);
}

static int	eeu(t_command *cmds, t_shell *shell, int fd[3][2], char **args)
{
	if (!(ft_strcmp(args[0], "env") == 0 || ft_strcmp(args[0], "echo") == 0
			|| ft_strcmp(args[0], "unset") == 0))
		return (0);
	if (connect_pipes(cmds, fd) == -1)
		return (-1);
	if (!direct_io(shell, cmds))
		return (-1);
	if (ft_strcmp(args[0], "env") == 0)
		fd[2][1] = env(&args[1], shell);
	else if (ft_strcmp(args[0], "echo") == 0)
		fd[2][1] = echo(&args[1], shell);
	else
		fd[2][1] = unset(shell, &args[1]);
	return (1);
}

int	check_builtin(t_command *cmds, t_shell *shell, int fd[3][2])
{
	char	**args;
	int		i;

	args = wraper(cmds->args, shell);
	if (!args)
		return (0);
	if (!args[0])
		return (free(args), 0);
	i = pce(cmds, shell, fd, args);
	if (i == -1 || i == 1)
		return (free_splits(args), i);
	i = eeu(cmds, shell, fd, args);
	if (i == -1 || i == 1)
		return (free_splits(args), i);
	free_splits(args);
	return (0);
}

static char	*tilde(char *str, t_shell *shell, int quote_type)
{
	t_env	*home_env;
	char	*home;
	char	*til;

	home_env = find_env(shell, "HOME");
	if (home_env)
		home = home_env->value;
	else
		home = "";
	if (*str == '~' && (str[1] == '\0' || str[1] == '/'))
		til = ft_strjoin(home, str + 1);
	else
		til = ft_strdup(str);
	if (!til)
		return (NULL);
	str = expand_str(shell, til, quote_type);
	return (free(til), str);
}

char	**wraper(t_token **args, t_shell *shell)
{
	int		count;
	int		j;
	char	**args_array;

	count = 0;
	while (args[count])
		count++;
	args_array = malloc(sizeof(char *) * (count + 1));
	if (!args_array)
		return (perror("could not create arguments list"), NULL);
	j = 0;
	while (j < count)
	{
		args_array[j] = tilde(args[j]->value, shell, args[j]->quote_type);
		if (!args_array[j])
			return (perror("could not create arguments list"),
				free_splits(args_array), NULL);
		j++;
	}
	args_array[j] = NULL;
	return (args_array);
}
