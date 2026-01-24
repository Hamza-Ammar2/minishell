/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpons <lpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 02:47:09 by lpons             #+#    #+#             */
/*   Updated: 2026/01/24 02:53:35 by lpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

static int	isvalid_lvl(char *str)
{
	if (!*str)
		return (0);
	if (*str == '+')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

static int	update_lvl(char *lvl, t_env *lvl_env)
{
	int		l;
	char	*lvl_new;

	l = ft_atoi(lvl) + 1;
	lvl_new = ft_itoa(l);
	if (!lvl_new)
		return (0);
	free(lvl_env->value);
	lvl_env->value = lvl_new;
	return (1);
}

int	init_lvl(t_shell *shell)
{
	t_env	*lvl_env;
	char	*lvl;

	lvl_env = find_env(shell, "SHLVL");
	if (!lvl_env)
		return (export((char *[]){
				"SHLVL=0", NULL}, shell));
	lvl = lvl_env->value;
	if (!isvalid_lvl(lvl))
		return (export((char *[]){
				"SHLVL=0", NULL}, shell));
	if (*lvl != '+')
		return (update_lvl(lvl, lvl_env));
	lvl = ft_strdup(lvl_env->value + 1);
	if (!lvl)
		return (0);
	free(lvl_env->value);
	return (lvl_env->value = lvl, 1);
}
