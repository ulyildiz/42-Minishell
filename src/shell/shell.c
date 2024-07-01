/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarac <ysarac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:33:38 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/07/01 19:06:51 by ysarac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

size_t	is_space(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] == ' ')
		i++;
	if (s[i] == '\0')
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
		return (clear_history(), 2);
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
		if (!executor(shell, shell->cmd, FALSE, 0))
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