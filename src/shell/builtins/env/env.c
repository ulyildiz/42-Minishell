/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:55:38 by ysarac            #+#    #+#             */
/*   Updated: 2024/07/07 12:22:55 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

static t_env	*create_env_node(t_env *src)
{
	t_env	*tmp;

	tmp = (t_env *)ft_calloc(1, sizeof(t_env));
	if (!tmp)
		return (NULL);
	if (src->name)
	{
		tmp->name = ft_strdup(src->name);
		if (!tmp->name)
			return (free(tmp), NULL);
	}
	if (src->value)
	{
		tmp->value = ft_strdup(src->value);
		if (!tmp->value)
			return (free(tmp->name), free(tmp), NULL);
	}
	else
	{
		tmp->value = ft_calloc(1, 1);
		if (!tmp->value)
			return (free(tmp->name), free(tmp), NULL);
	}
	return (tmp);
}

static void	copy_env(t_env **export, t_env *src)
{
	t_env	*tmp;

	while (src)
	{
		tmp = create_env_node(src);
		if (!tmp)
		{
			free_env(*export);
			return ;
		}
		list_add_back(export, tmp);
		src = src->next;
	}
}

static void	update_or_add_env(t_env **export, char *str, t_main *shell)
{
	t_env	*tmp;
	char	**split;
	t_env	*env_var;

	split = ft_split(str, '=');
	if (!split)
		return (exit_for_fork(shell));
	env_var = find_env(*export, split[0]);
	if (!env_var)
		return (free_double(split));
	if (split[0])
	{
		if (split[1])
			find_env(*export, split[0])->value = split[1];
	}
	else if (split[0] && find_env(*export, split[0]) == NULL)
	{
		tmp = (t_env *)malloc(sizeof(t_env));
		if (!tmp)
			return ;
		tmp->name = split[0];
		tmp->value = "\0";
		if (split[1])
			tmp->value = ft_strdup(split[1]);
		tmp->next = NULL;
		list_add_back(export, tmp);
	}
	free_double(split);
}

static void	print_env(t_env *env, int fd)
{
	while (env)
	{
		ft_putstr_fd(env->name, fd);
		if (env->value && env->value[0] != '\0')
		{
			ft_putstr_fd("=", fd);
			ft_putstr_fd(env->value, fd);
		}
		ft_putstr_fd("\n", fd);
		env = env->next;
	}
}

void	env(t_command *cmds, t_main *shell)
{
	t_env	*export;
	int		i;

	i = 1;
	export = NULL;
	copy_env(&export, shell->envs);
	while (cmds->value[i])
		update_or_add_env(&export, cmds->value[i++], shell);
	print_env(export, cmds->fd[1]);
	free_env(export);
}
// d0nE