/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 18:11:51 by ysarac            #+#    #+#             */
/*   Updated: 2024/07/22 16:25:23 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"
#include <stdlib.h>

int	handle_builtin_exit(t_bool cmd_num)
{
	shell_keeper(NULL)->es = 12;
	if (cmd_num)
		exit_for_fork(shell_keeper(NULL));
	else
		exit_in_exec(shell_keeper(NULL));
	return (0);
}

int	execute_command(t_command *cmds, t_bool cmd_num, t_build *command,
		char *tmp)
{
	free(tmp);
	if (!command->func(cmds, shell_keeper(NULL)))
	{
		return (handle_builtin_exit(cmd_num));
	}
	if (cmd_num)
		exit_for_fork(shell_keeper(NULL));
	return (0);
}
