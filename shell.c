/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:33:38 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/06/06 10:49:12 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"
#include "42-libft/libft.h"
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>

static int	line_read(t_main *shell)
{
	shell->cmd_line = readline(shell->prompt);
	if (!shell->cmd_line)
		return (rl_clear_history(), perror("Readline"), 2);
	else if (!is_space(shell->cmd_line))
		return (free(shell->cmd_line), 0);
	add_history(shell->cmd_line);
	return (1);
}

void	start_shell(t_main *shell)
{
	int i;

	while(1)
	{
		i = line_read(shell);
		if (!i)
			continue ;
		else if (i == 2)
			break;
		if (!lexer(shell))
			break;
/* 		if (!expender(shell))
			break; */
/* 		if (!parser(shell, shell->token, 0))
			break; */
/* 		if (!executor(shell))
			break; */
		//update veya free?
		shell->control = 1;
	}

}

/* 		while(shell->token)
		{
			printf("%s -", shell->token->value);
			shell->token = shell->token->next;
		}
		printf("\n"); */