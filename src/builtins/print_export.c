/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haammar <haammar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 06:18:31 by haammar           #+#    #+#             */
/*   Updated: 2026/02/14 06:34:36 by haammar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

static void	bsort(t_env **args)
{
	int		i;
	int		swapped;
	t_env	*tmp;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		i = 0;
		while (args[i + 1])
		{
			if (ft_strcmp(args[i]->key, args[i + 1]->key) > 0)
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

static void print_exp(t_env **envs)
{
    int i;

    i = 0;
    bsort(envs);
	while (envs[i])
	{
		if (envs[i]->key[0] == '_' && envs[i]->key[1] == '=')
		{
			i++;
			continue ;
		}
        ft_fprintf(STDOUT_FILENO, "declare -x %s", envs[i]->key);
        if (envs[i]->value)
            ft_fprintf(STDOUT_FILENO, "=%s", envs[i]->value);
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
    free(envs);
}

int	print_export(t_shell *shell)
{
	t_env	*env;
    t_env   **envs;
	int		l;

	l = 0;
	env = shell->env;
	while (env)
	{
		l++;
		env = env->next;
	}
	envs = malloc(sizeof(t_env *) * (l + 1));
    if (!envs)
        return (perror("print_export: malloc failed"), 1);
    env = shell->env;
    l = 0;
    while (env)
    {
        envs[l] = env;
        l++;
        env = env->next;
    }
    envs[l] = NULL;
    return (print_exp(envs), 0);
}
