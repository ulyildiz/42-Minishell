/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 06:52:43 by ysarac            #+#    #+#             */
/*   Updated: 2024/06/29 16:59:32 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

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
		while ((*env)[i] &&(*env)[i] != '=')
			i++;
		tmp->name = ft_substr(*env, 0, i);
		if (!tmp->name)
			return (free(tmp), free_env(shell->envs), 0);
		tmp->value = ft_substr(*env, ++i, ft_strlen(&(*env)[i]));
		if (!tmp->value)
			return (free(tmp->value), free(tmp), free_env(shell->envs), 0);
		tmp->next = NULL;
		list_add_back(&(shell->envs), tmp);
		env++;
	}
	return (1);
}

int	initialize(t_main *shell, char **env)
{
	shell->cmd = NULL;
	shell->token = NULL;
	shell->paths = NULL;
	shell->envs = NULL;
	shell->cmd_line = NULL;
	shell->prompt = "ft_sh-> ";
	shell->paths = NULL;
	shell->exit_status = 0;
	if (!init_env(shell, env))
		return (0);
	shell->control = 1;
	shell->env_for_execve_function = NULL;
	if (!update_env(shell))
		(free_env(shell->envs), 0);
	return (1);
}
