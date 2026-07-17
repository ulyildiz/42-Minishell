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

int	env(t_command *cmds, t_main *shell)
{
	if (!check_for_options(cmds))
		return (shell->es = 1, 1);
	print_env(shell->envs, cmds->fd[1]);
	return (shell->es = 0, 1);
}
