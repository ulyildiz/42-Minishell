/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:55:38 by ysarac            #+#    #+#             */
/*   Updated: 2024/07/09 23:22:44 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

extern int	copy_env(t_env **export, t_env *src);

static int	add_new_env_var(t_env **export, char **split)
{
	t_env	*tmp;

	tmp = (t_env *)malloc(sizeof(t_env));
	if (!tmp)
		return (0);
	tmp->name = split[0];
	tmp->value = "\0";
	if (split[1])
		tmp->value = ft_strdup(split[1]);
	tmp->next = NULL;
	list_add_back(export, tmp);
	return (1);
}

static int	update_env_var(t_env **export, char **split)
{
	t_env	*env_var;

	env_var = find_env(*export, split[0]);
	if (env_var && split[1])
	{
		env_var->value = split[1];
		return (1);
	}
	return (0);
}

static int	update_or_add_env(t_env **export, char *str, t_main *shell)
{
	char	**split;
	int		result;

	split = ft_split(str, '=');
	if (!split)
	{
		exit_for_fork(shell);
		return (0);
	}
	if (find_env(*export, split[0]))
		result = update_env_var(export, split);
	else
		result = add_new_env_var(export, split);
	free_double(split);
	return (result);
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
	if (!check_for_options(cmds))
		return (1);
	if (!copy_env(&export, shell->envs))
		return (0);
	while (cmds->value[i])
	{
		if (!update_or_add_env(&export, cmds->value[i++], shell))
			return (0);
	}
	print_env(export, cmds->fd[1]);
	free_env(export);
	return (1);
}
