/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haammar <haammar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 03:03:43 by lpons             #+#    #+#             */
/*   Updated: 2026/02/17 21:25:13 by haammar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

static char	**pathify(char *path)
{
	char	**paths;
	char	**pathy;
	int		i;

	paths = ft_split(path, ':');
	if (path[0] != ':' && path[ft_strlen(path) - 1] != ':')
		return (paths);
	i = 0;
	while (paths[i])
		i++;
	pathy = malloc(sizeof(char *) * (i + 2));
	if (!pathy)
		return (perror("pathify: malloc failed"), free_splits(paths), NULL);
	i = 0;
	while (paths[i])
	{
		pathy[i] = paths[i];
		i++;
	}
	free(paths);
	pathy[i] = ft_strdup(".");
	if (!pathy[i])
		return (perror("pathify: malloc failed"), free_splits(pathy), NULL);
	pathy[i + 1] = NULL;
	return (pathy);
}

char	**get_paths(t_shell *shell)
{
	char	*path;
	char	**paths;
	t_env	*env_node;

	env_node = find_env(shell, "PATH");
	if (!env_node || !env_node->value || !env_node->value[0])
	{
		paths = malloc(sizeof(char *) * 2);
		if (!paths)
			return (perror("get_paths: malloc failed"), NULL);
		paths[0] = ft_strdup(".");
		if (!paths[0])
			return (perror("get_paths: malloc failed"), free(paths), NULL);
		paths[1] = NULL;
		return (paths);
	}
	path = env_node->value;
	paths = pathify(path);
	return (paths);
}

char	*create_path(char *path, char *cmd)
{
	char	*full_path;
	int		i;
	int		j;

	i = 0;
	full_path = malloc(ft_strlen(path) + ft_strlen(cmd) + 2);
	if (!full_path)
		return (perror("create_path: malloc failed"), NULL);
	while (path[i])
	{
		full_path[i] = path[i];
		i++;
	}
	full_path[i] = '/';
	i++;
	j = 0;
	while (cmd[j])
	{
		full_path[i + j] = cmd[j];
		j++;
	}
	return (full_path[i + j] = '\0', full_path);
}

char	*get_path(char **paths, char *cmd)
{
	char	*full_path;

	if (ft_strchr(cmd, '/') && access(cmd, F_OK) == 0)
		return (cmd);
	if (!paths)
		return (NULL);
	while (*paths)
	{
		full_path = create_path(*paths, cmd);
		if (!full_path)
			return (NULL);
		if (access(full_path, F_OK) == 0)
			return (full_path);
		free(full_path);
		paths++;
	}
	return (NULL);
}

int	restore(t_shell *shell)
{
	if (dup2(shell->stdin_backup, STDIN_FILENO) == -1)
		return (perror("restore: dup2 failed"), 1);
	if (dup2(shell->stdout_backup, STDOUT_FILENO) == -1)
		return (perror("restore: dup2 failed"), 1);
	return (0);
}
