/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:57:43 by ysarac            #+#    #+#             */
/*   Updated: 2024/07/22 16:48:52 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"
#include "libft.h"
#include <stdlib.h>

extern char		*ft_exportdup(const char *s1);
extern t_env	*sort_export(t_env *lst, int (*cmp)(int, int));
extern int		ascending(int a, int b);
extern int		handle_invalid_identifier(t_command *cmd, t_main *shell, int i);
extern int		handle_assignment(t_command *cmd, t_env *envs, char *eq_pos,
					int i);
extern int		update_or_add_env_var(t_env **envs, char *name, char *value);
extern int		all_alphanumeric(char *str, int i);

int	add_new_env(t_env **envs, char *name, char *value)
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

int	process_commands(t_command *cmds, t_main *shell, int i)
{
	char	*eq_pos;
	t_env	*env_var;

	while (cmds->value[++i])
	{
		eq_pos = ft_strchr(cmds->value[i], '=');
		if (eq_pos == NULL)
			eq_pos = cmds->value[i] + ft_strlen(cmds->value[i]);
		env_var = find_env(shell->envs, cmds->value[i]);
		if (ft_isdigit(cmds->value[i][0]) || cmds->value[i][0] == '=')
			return (handle_invalid_identifier(cmds, shell, i), 0);
		else if (!all_alphanumeric(cmds->value[i], eq_pos - cmds->value[i]))
			return (handle_invalid_identifier(cmds, shell, i), 0);
		else if (eq_pos != NULL)
		{
			if (handle_assignment(cmds, shell->envs, eq_pos, i))
				return (shell->es = 1, exit_for_fork(shell), 1);
		}
		else if (env_var == NULL)
		{
			if (add_new_env(&shell->envs, cmds->value[i], NULL))
				return (shell->es = 1, exit_for_fork(shell), 1);
		}
	}
	return (shell->es = 0, 0);
}

int	copy_env(t_env **export, t_env *src)
{
	t_env	*tmp;

	while (src)
	{
		tmp = (t_env *)malloc(sizeof(t_env));
		if (!tmp)
			return (free_env(*export), 0);
		tmp->next = NULL;
		tmp->name = ft_strdup(src->name);
		if (!tmp->name)
			return (free(tmp), free_env(*export), 0);
		tmp->value = ft_exportdup(src->value);
		if (tmp->value == (void *)1)
			return (free(tmp->name), free(tmp), free_env(*export), 0);
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
	if (!check_for_options(cmds))
		return (shell->es = 1, 1);
	if (process_commands(cmds, shell, 0))
		return (0);
	if (update_env(shell) == 0)
		return (0);
	if (!copy_env(&export, shell->envs))
		return (0);
	export = sort_export(export, ascending);
	if (!export)
		return (0);
	if (cmds->value[1] == NULL)
		print_export(export, cmds->fd[1]);
	if (update_env(shell) == 0)
		return (0);
	free_env(export);
	return (1);
}
