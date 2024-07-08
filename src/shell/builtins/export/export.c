/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:57:43 by ysarac            #+#    #+#             */
/*   Updated: 2024/07/08 14:58:23 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

extern char	*ft_exportdup(const char *s1);
static int	add_new_env(t_env **envs, char *name, char *value)
{
	t_env	*tmp;

	tmp = (t_env *)ft_calloc(1, sizeof(t_env));
	if (!tmp)
		return (1);
	tmp->name = ft_strdup(name);
	if (!tmp->name)
	{
		free(tmp);
		return (1);
	}
	tmp->value = ft_exportdup(value);
	if (tmp->value == (void *)1)
	{
		free(tmp->name);
		free(tmp);
		return (1);
	}
	tmp->next = NULL;
	list_add_back(envs, tmp);
	return (0);
}

static int	process_commands(t_command *cmds, t_main *shell)
{
	char	*eq_pos;
	char	*name;
	char	*value;
	int		i;
	t_env	*env_var;

	i = 1;
	while (cmds->value[i])
	{
		if (ft_isdigit(cmds->value[i][0]) || cmds->value[i][0] == '=')
		{
			ft_putstr_fd("ft_sh: export: ", cmds->fd[1]);
			ft_putstr_fd(cmds->value[i], cmds->fd[1]);
			ft_putendl_fd(" : not a valid identifier", cmds->fd[1]);
			shell->exit_status = 1;
		}
		else
		{
			eq_pos = ft_strchr(cmds->value[i], '=');
			if (eq_pos != NULL)
			{
				name = ft_substr(cmds->value[i], 0, eq_pos - cmds->value[i]);
				if (!name)
					return (1);
				value = ft_exportdup(eq_pos + 1);
				if (value == (void *)1)
					return (free(name), 1);
				env_var = find_env(shell->envs, name);
				if (env_var)
				{
					if (env_var->value)
						free(env_var->value);
					env_var->value = ft_strdup(value);
					free(name);
					free(value);
					if (env_var->value == (void *)1)
						return (1);
				}
				else
				{
					add_new_env(&shell->envs, name, value);
					free(name);
					free(value);
				}
			}
			else
			{
				env_var = find_env(shell->envs, cmds->value[i]);
				if (!env_var)
					add_new_env(&shell->envs, cmds->value[i], NULL);
			}
		}
		i++;
	}
	return (0);
}

void	copy_env(t_env **export, t_env *src)
{
	t_env	*tmp;

	while (src)
	{
		tmp = (t_env *)malloc(sizeof(t_env));
		if (!tmp)
			return (free_env(*export));
		tmp->next = NULL;
		tmp->name = ft_strdup(src->name);
		if (!tmp->name)
			return (free(tmp), free_env(*export));
		tmp->value = ft_exportdup(src->value);
		if (tmp->value == (void *)1)
			return (free(tmp->name), free(tmp), free_env(*export));
		list_add_back(export, tmp);
		src = src->next;
	}
}

static void	print_export(t_env *env, int fd)
{
	if (!env)
		return ;
	while (env)
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(env->name, fd);
		if (env->value)
		{
			ft_putstr_fd("=\"", fd);
			ft_putstr_fd(env->value, fd);
			ft_putstr_fd("\"\n", fd);
		}
		else
			ft_putstr_fd("\n", fd);
		env = env->next;
	}
}

void	export(t_command *cmds, t_main *shell)
{
	t_env	*export;

	export = NULL;
	process_commands(cmds, shell);
	if (update_env(shell) == 0)
		return ;
	copy_env(&export, shell->envs);
	export = sort_export(export, ascending);
	if (cmds->value[1] == NULL)
		print_export(export, cmds->fd[1]);
	update_env(shell);
	free_env(export);
}
