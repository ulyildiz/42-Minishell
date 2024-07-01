/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarac <ysarac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 06:52:43 by ysarac            #+#    #+#             */
/*   Updated: 2024/07/01 13:12:32 by ysarac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

t_env	*find_env(t_env *envs, char *wanted)
{
	if (!wanted)
		return (NULL);
	while (envs)
	{
		if (!ft_strncmp(envs->name, wanted, ft_strlen(wanted)))
			return (envs);
		envs = envs->next;
	}
	return (NULL);
}

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
// env_for_execve_function güncellemek için ama exporta eklenmedi

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
		new_env[i] = ft_strappend(new_env[i], tmp->value,
				ft_strlen(tmp->value));
		if (!new_env[i++])
			return (free_double(new_env), 0);
		tmp = tmp->next;
	}
	new_env[i] = NULL;
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
