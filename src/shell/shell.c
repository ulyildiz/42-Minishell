/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:33:38 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/06/29 13:07:27 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

static int	line_read(t_main *shell)
{
	shell->cmd_line = readline(shell->prompt);
	if (!shell->cmd_line)
	{
		free_env(shell->envs);
		free_double(shell->env_for_execve_function);
		return (rl_clear_history(), 2);
	}
	else if (!is_space(shell->cmd_line))
		return (free(shell->cmd_line), 0);
	add_history(shell->cmd_line);
	return (1);
}

void	start_shell(t_main *shell)
{
	int			i;

	while (1)
	{
		i = line_read(shell);
		if (!i)
			continue ;
		else if (i == 2)
			break ;
		if (!lexer(shell))
			break ;
		if (!expender(shell))
			break ;
		if (!parser(shell, shell->token, 0))
			break ;
		if (!executor(shell))
			break ;
		shell->control = 1;
	}
}

/* 		t = shell->token;
		while(t)
		{
			printf("-%s -> expend_va = %d -> type_va = %d\n", t->value,
					t->is_expend, t->type);
			t = t->next;
		}
		printf("\n"); */