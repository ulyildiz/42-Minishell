/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:55:38 by ysarac            #+#    #+#             */
/*   Updated: 2024/07/10 02:39:34 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"
#include "libft.h"

extern int		copy_env(t_env **export, t_env *src);
extern int		handle_invalid_identifier(t_command *cmd, t_main *shell, int i);
extern int		handle_assignment(t_command *cmd, t_env *envs, char *eq_pos,
					int i);
extern int		all_alphanumeric(char *str, int i);
extern int		add_new_env(t_env **envs, char *name, char *value);
extern void		error_handler(t_command *cmds, int flag, t_main *shell);

static void	print_env(t_env *env, int fd)
{
	while (env)
	{
		if (env->value && env->name)
		{
			ft_putstr_fd(env->name, fd);
			ft_putstr_fd("=", fd);
			ft_putendl_fd(env->value, fd);
		}
		env = env->next;
	}
}

int	process_command2(t_command *cmds, t_env *export, t_main *shell, int i)
{
	char	*eq_pos;
	t_env	*env_var;

	while (cmds->value[++i])
	{
		eq_pos = ft_strchr(cmds->value[i], '=');
		env_var = find_env(export, cmds->value[i]);
		if (cmds->value[i][0] == '=')
			handle_invalid_identifier(cmds, shell, i);
		else if (eq_pos == NULL)
			return (error_handler(cmds, 2, shell), 1);
		else if (eq_pos != NULL)
		{
			if (handle_assignment(cmds, export, eq_pos, i))
				return (shell->exit_status = 1, exit_for_fork(shell), 1);
		}
		else if (env_var == NULL)
		{
			if (add_new_env(&export, cmds->value[i], NULL))
				return (shell->exit_status = 1, exit_for_fork(shell), 1);
		}
	}
	return (0);
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
	if (!process_command2(cmds, export, shell, 0))
		print_env(export, cmds->fd[1]);
	free_env(export);
	return (1);
}
