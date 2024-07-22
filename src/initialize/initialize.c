/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 06:52:43 by ysarac            #+#    #+#             */
/*   Updated: 2024/07/22 17:08:44 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "functions.h"
#include <stdlib.h>
#include <stdio.h>

int	env_len(t_main *shell)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = shell->envs;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

int	update_env(t_main *shell)
{
	char	**new_env;
	t_env	*tmp;
	size_t	i;

	i = 0;
	new_env = (char **)ft_calloc(env_len(shell) + 1, sizeof(char *));
	if (!new_env)
		return (perror("Update env"), 0);
	tmp = shell->envs;
	while (tmp)
	{
		new_env[i] = ft_strjoin(tmp->name, "=");
		if (!new_env[i])
			return (free_double(new_env), 0);
		if (tmp->value)
			new_env[i] = ft_strappend(new_env[i], tmp->value,
					ft_strlen(tmp->value));
		if (!new_env[i++])
			return (free_double(new_env), 0);
		tmp = tmp->next;
	}
	if (shell->env_for_execve_function)
		free_double(shell->env_for_execve_function);
	shell->env_for_execve_function = new_env;
	return (1);
}

static int	init_env(t_main *shell, char **env)
{
	t_env	*tmp;
	size_t	i;

	shell->envs = NULL;
	while (*env)
	{
		i = 0;
		tmp = (t_env *)malloc(sizeof(t_env));
		if (!tmp)
			return (free_env(shell->envs), 0);
		while ((*env)[i] && (*env)[i] != '=')
			i++;
		tmp->name = ft_substr(*env, 0, i++);
		if (!tmp->name)
			return (free(tmp), free_env(shell->envs), 0);
		tmp->value = ft_substr(*env, i, ft_strlen(&(*env)[i]));
		if (!tmp->value)
			return (free(tmp->value), free(tmp), free_env(shell->envs), 0);
		tmp->next = NULL;
		list_add_back(&(shell->envs), tmp);
		env++;
	}
	return (1);
}

int	shell_level(t_env *env)
{
	int	i;

	if (!env)
		return (1);
	i = ft_atoi(env->value);
	if (i < 0)
		i = 0;
	else
		i++;
	if (env->value)
		free(env->value);
	env->value = ft_itoa(i);
	if (!env->value)
		return (0);
	return (1);
}

int	initialize(t_main *shell, char **env)
{
	shell->cmd = NULL;
	shell->token = NULL;
	shell->paths = NULL;
	shell->envs = NULL;
	shell->cmd_line = NULL;
	shell->prompt = "ft_sh: ";
	shell->paths = NULL;
	shell->es = 0;
	if (!init_env(shell, env))
		return (shell->es = 12, 0);
	if (!shell_level(find_env(shell->envs, "SHLVL")))
		return (free_env(shell->envs), shell->es = 12, 0);
	shell->control = 1;
	shell->env_for_execve_function = NULL;
	if (!update_env(shell))
		return (free_env(shell->envs), shell->es = 12, 0);
	return (1);
}
