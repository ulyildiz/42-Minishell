/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:33:38 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/07/22 16:42:44 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

size_t	is_space(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] == ' ')
		i++;
	if (i != 0 && s[i] == '\0')
		return (0);
	return (1);
}

static int	line_read(t_main *shell)
{
	shell->cmd_line = readline(shell->prompt);
	if (!shell->cmd_line)
	{
		free_env(shell->envs);
		free_double(shell->env_for_execve_function);
		return (rl_clear_history(), 2);
	}
	else if (!shell->cmd_line[0])
		return (free(shell->cmd_line), 0);
	else if (!is_space(shell->cmd_line))
		return (add_history(shell->cmd_line), free(shell->cmd_line), 0);
	else
		add_history(shell->cmd_line);
	return (1);
}

void	start_shell(t_main *shell)
{
	int	i;

	while (1)
	{
		i = line_read(shell);
		if (!i)
			continue ;
		else if (i == 2)
			break ;
		lexer(shell);
		parser(shell, shell->token, 0, NULL);
		expender(shell);
		executor(shell, shell->cmd, FALSE, 0);
		signal_reciever(1);
		shell->control = 1;
	}
}
