/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:56:36 by ysarac            #+#    #+#             */
/*   Updated: 2024/07/08 15:03:58 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

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

char	*append_path(char *base, char *append)
{
	char	*path;
	char	*tmp;

	path = ft_strjoin(base, "/");
	if (!path)
		return (NULL);
	tmp = ft_strappend(path, append, ft_strlen(append));
	if (!tmp)
		return (free(path), NULL);
	return (tmp);
}

void	change_directory_and_update_envs(t_main *shell, char *path,
		char *old_pwd_value)
{
	char	*gtcwd;
	static int i = 0;

	if (chdir(path) == 0)
	{
		gtcwd = getcwd(NULL, 0);
		if (!update_or_create_env(&shell->envs, "OLDPWD", old_pwd_value))
		{
			free(gtcwd);
			free(path);
			perror("update_or_create_env failed");
			shell->exit_status = 1;
			exit_for_fork(shell);
		}
		if (!update_or_create_env(&shell->envs, "PWD", gtcwd) || i == 4)
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
	i++;
}
