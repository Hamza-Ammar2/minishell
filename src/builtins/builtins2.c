/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haammar <haammar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 03:01:09 by lpons             #+#    #+#             */
/*   Updated: 2026/02/07 09:15:09 by haammar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

static int	isvalid_key(char *str)
{
	char	*end;
	char	*tmp;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	str++;
	end = ft_strnstr(str, "+=", ft_strlen(str));
	tmp = ft_strchr(str, '=');
	if (tmp < end || !end)
		end = tmp;
	while (*str && str != end)
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		str++;
	}
	return (1);
}

void	bsort(char **args)
{
	int		i;
	int		swapped;
	char	*tmp;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		i = 0;
		while (args[i + 1])
		{
			if (ft_strcmp(args[i], args[i + 1]) > 0)
			{
				tmp = args[i];
				args[i] = args[i + 1];
				args[i + 1] = tmp;
				swapped = 1;
			}
			i++;
		}
	}
}

static int	print_export(t_shell *shell)
{
	char	**args;
	int		i;

	i = 0;
	args = env2arr(shell->env);
	if (!args)
		return (perror("print_export: malloc failed"), 1);
	bsort(args);
	while (args[i])
	{
		if (args[i][0] == '_' && args[i][1] == '=')
		{
			i++;
			continue ;
		}
		write(STDOUT_FILENO, "declare -x ", 11);
		write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
	return (free_splits(args), 0);
}

static int	handle_pe(t_shell *shell, char *arg)
{
	char	*eq;
	char	*peq;

	eq = ft_strchr(arg, '=');
	peq = ft_strnstr(arg, "+=", ft_strlen(arg));
	if (eq < peq || !peq)
		return (exp_one(shell, arg));
	return (exp_one_peq(shell, arg, peq));
}

int	export(char **args, t_shell *shell)
{
	int	exit_status;

	if (!*args)
		return (print_export(shell));
	exit_status = 0;
	while (*args)
	{
		if (!isvalid_key(*args))
		{
			ft_fprintf(2, "export: `%s': not a valid identifier\n", *args);
			args++;
			exit_status = 1;
			continue ;
		}
		if (!handle_pe(shell, *args))
			return (1);
		args++;
	}
	return (exit_status);
}
