/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:56:36 by ysarac            #+#    #+#             */
/*   Updated: 2024/07/10 02:38:16 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

static t_env	*create_env(char *name, char *value)
{
	t_env	*env;

	env = (t_env *)malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->name = ft_strdup(name);
	if (!env->name)
		return (free(env), NULL);
	if (value)
	{
		env->value = ft_strdup(value);
		if (!env->value)
			return (free(env->name), free(env), NULL);
	}
	else
		env->value = "\0";
	env->next = NULL;
	return (env);
}

static int	set_env_value(t_env *env, char *value)
{
	if (env->value)
		free(env->value);
	if (value)
	{
		env->value = ft_strdup(value);
		if (!env->value)
			return (-1);
	}
	else
		env->value = "\0";
	return (0);
}

t_env	*update_or_create_env(t_env **envs, char *name, char *value)
{
	t_env	*env;

	if (!value)
		return (NULL);
	env = find_env(*envs, name);
	if (!env || !env->value)
	{
		env = create_env(name, value);
		if (!env)
			return (NULL);
		list_add_back(envs, env);
	}
	else if (env && env->value[0] == '\0')
		env->value = getcwd(NULL, 0);
	else if (env && env->value)
	{
		if (set_env_value(env, value) != 0)
			return (NULL);
	}
	return (env);
}

void	change_directory_and_update_envs(t_main *shell, char *path,
		char *old_pwd_value)
{
	char	*gtcwd;

	if (chdir(path) == 0)
	{
		gtcwd = getcwd(NULL, 0);
		if (!gtcwd)
		{
			free(path);
			perror("getcwd");
			shell->exit_status = 1;
			exit_for_fork(shell);
		}
		if (!update_or_create_env(&shell->envs, "OLDPWD", old_pwd_value)
			|| !update_or_create_env(&shell->envs, "PWD", gtcwd))
		{
			free(gtcwd);
			free(path);
			perror("update_or_create_env failed");
			shell->exit_status = 1;
			exit_for_fork(shell);
		}
		free(gtcwd);
	}
	else
		perror("cd");
}
