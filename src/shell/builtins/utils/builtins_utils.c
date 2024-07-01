/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 17:30:01 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/06/29 17:32:00 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

int	is_builtin(t_command *cmds, t_main *shell, t_bool cmd_num)
{
	int				i;
	static t_build	commands[] = {{"echo", echo}, {"cd", cd}, {"pwd", pwd},
			{"env", env}, {"unset", unset}, {"export", export}, {"exit",
			exit_cmd}, {NULL, NULL}};

	i = 0;
	while (commands[i].name)
	{
		if (ft_strncmp(ft_strlower(cmds->value[0]), commands[i].name,
				ft_strlen(cmds->value[0])) == 0) // ana value küçültülüyor 
		{
			commands[i].func(cmds, shell);
			if (cmd_num)
				exit_for_fork(shell);
			else
				return (0);
		}
		i++;
	}
	return (1);
}
