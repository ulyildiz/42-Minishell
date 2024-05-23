/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:33:54 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/05/23 11:33:54 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"
#include "42-libft/libft.h"
#include <stdio.h>

int	executor(t_main *shell)
{
	int i;
	i = 0;
	t_command *tmp = shell->cmd;
	t_command *cmds;

	cmds = shell->cmd;
	while(cmds)
	{
		if (!is_builtlin(cmds))
			;
		else if (accessibility(shell))
			//klasik execve
			;
		else
			return (ft_putstr_fd("ft_sh: command not found: ", 2),
				ft_putstr_fd(cmds->value[0], 2), ft_putchar_fd('\n', 2), 2);
		cmds = cmds->next;
	}


	printf("\n");
	while (tmp)
	{
		i = 0;
		while (tmp->value[i])
		{
			printf("%s ", tmp->value[i]);
			i++;
		}
		printf("where_p = %d - where_r = %d\n", tmp->where_p, tmp->where_r);
		tmp = tmp->next;
	}

	return (1);
}