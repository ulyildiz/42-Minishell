/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:56:06 by ysarac            #+#    #+#             */
/*   Updated: 2024/07/04 18:20:05 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

int	is_all_numeric(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	exit_cmd(t_command *cmds, t_main *shell)
{
	size_t	i;

	i = 0;
	while (cmds->value[i])
		i++;
	ft_putstr_fd("exit", cmds->fd[1]);
	ft_putstr_fd("\n", cmds->fd[1]);
	if (i > 1)
	{
		if (is_all_numeric(cmds->value[1]))
		{
			shell->exit_status = ft_atoi(cmds->value[1]);
			if (i > 2)
			{
				ft_putstr_fd("exit: too many arguments\n", 2);
				shell->exit_status = 1;
			}
		}
		else
		{
			ft_putstr_fd("exit: numeric argument required\n", 2);
			shell->exit_status = 255;
		}
	}
	else
		shell->exit_status = 0;
	exit_for_fork(shell); //?
	
}
//exit a    numric de çık
//exit a 3 numeric öazım de çık
//exit 3 3 çık code=1 to much arg
