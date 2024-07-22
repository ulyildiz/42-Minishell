/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:56:06 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/07/22 17:02:28 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"
#include "libft.h"

static int	is_all_numeric(char *str)
{
	size_t	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	exit_cmd(t_command *cmds, t_main *shell)
{
	size_t	i;

	i = 0;
	while (cmds->value[i])
		i++;
	ft_putendl_fd("exit", cmds->fd[1]);
	if (i > 1)
	{
		if (is_all_numeric(cmds->value[1]))
		{
			shell->es = (ft_atoi(cmds->value[1]) % 256);
			if (i > 2)
				return (shell->es = 1,
					ft_putendl_fd("exit: too many arguments", 2),
					1);
		}
		else
		{
			ft_putstr_fd("exit: numeric argument required\n", 2);
			shell->es = 255;
		}
	}
	exit_for_fork(shell);
	return (1);
}
