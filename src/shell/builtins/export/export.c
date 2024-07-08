/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarac <yunusemresarac@yaani.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:57:43 by ysarac            #+#    #+#             */
/*   Updated: 2024/07/08 17:09:07 by ysarac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

char *ft_exportdup(const char *s1);
t_env	*sort_export(t_env *lst, int (*cmp)(int, int));
int	ascending(int a, int b);

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

int	copy_env(t_env **export, t_env *src)
{
	t_env	*tmp;

	while (src)
	{
		tmp = (t_env *)malloc(sizeof(t_env));
		if (!tmp)
			return (free_env(*export),0);
		tmp->next = NULL;
		tmp->name = ft_strdup(src->name);
		if (!tmp->name)
			return (free(tmp), free_env(*export),0);
		tmp->value = ft_exportdup(src->value);
		if (tmp->value == (void *)1)
			return (free(tmp->name), free(tmp), free_env(*export),0);
		list_add_back(export, tmp);
		src = src->next;
	}
	return (1);
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

int	export(t_command *cmds, t_main *shell)
{
	t_env	*export;

	export = NULL;
	if(process_commands(cmds, shell))
		return (0);
	if (update_env(shell) == 0)
		return(0) ;
	if(!copy_env(&export, shell->envs))
		return (0);
	export = sort_export(export, ascending);
	if(!export)
		return (0);
	if (cmds->value[1] == NULL)
		print_export(export, cmds->fd[1]);
	if (update_env(shell) == 0)
		return(0) ;
	free_env(export);
	return (1);	
}
