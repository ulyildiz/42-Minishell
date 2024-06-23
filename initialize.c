/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:33:18 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/06/11 14:47:39 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42-libft/libft.h"
#include "functions.h"
#include <stdio.h>
#include <stdlib.h>

static int	prompt(t_main *shell)
{
	shell->prompt = ft_strdup("ft_sh-> ");
	if (!shell->prompt)
		return (0);
	return (1);
}

static int	init_env(t_main *shell, char **env)
{
	t_env	*tmp;
	char	**s;

	shell->envs = NULL;
	while (*env)
	{
		tmp = (t_env *)malloc(sizeof(t_env));
		if (!tmp)
			return (free_env(shell->envs), 0);
		s = ft_split(*env, '=');
		if (!s)
			return (free(tmp), free_env(shell->envs), 0);
		tmp->name = s[0];
		tmp->value = s[1];
		tmp->next = NULL;
		list_add_back(&(shell->envs), tmp);
		free(s);
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
	shell->prompt = NULL;
	shell->paths = NULL;
	if (!prompt(shell))
		return (0);
	if (!init_env(shell, env))
		return (free(shell->prompt), 0);
	shell->control = 1;
	shell->env_for_execve_function = env;
	return (1);
}
