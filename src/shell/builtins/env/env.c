/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarac <yunusemresarac@yaani.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:55:38 by ysarac            #+#    #+#             */
/*   Updated: 2024/07/08 16:58:50 by ysarac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

extern int	copy_env(t_env **export, t_env *src);

static int	update_or_add_env(t_env **export, char *str, t_main *shell)
{
	t_env	*tmp;
	char	**split;
	t_env	*env_var;

	split = ft_split(str, '=');
	if (!split)
		return (exit_for_fork(shell),0);
	env_var = find_env(*export, split[0]);
	if (!env_var)
		return (free_double(split),0);
	if (split[0])
	{
		if (split[1])
			find_env(*export, split[0])->value = split[1];
	}
	else if (split[0] && find_env(*export, split[0]) == NULL)
	{
		tmp = (t_env *)malloc(sizeof(t_env));
		if (!tmp)
			return (0);
		tmp->name = split[0];
		tmp->value = "\0";
		if (split[1])
			tmp->value = ft_strdup(split[1]);
		tmp->next = NULL;
		list_add_back(export, tmp);
	}
	free_double(split);
	return (1);
}

static void	print_env(t_env *env, int fd)
{
	while (env)
	{
		if (env->value)
		{
			ft_putstr_fd(env->name, fd);
			ft_putstr_fd("=", fd);
			ft_putendl_fd(env->value, fd);
		}
		env = env->next;
	}
}

int	env(t_command *cmds, t_main *shell)
{
	t_env	*export;
	int		i;

	i = 1;
	export = NULL;
	if(!copy_env(&export, shell->envs))
		return (0);
	while (cmds->value[i])
	{
		if(!update_or_add_env(&export, cmds->value[i++], shell))
			return (0);
	}
	print_env(export, cmds->fd[1]);
	free_env(export);
	return(1);
}
// d0nE