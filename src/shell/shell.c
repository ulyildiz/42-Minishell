/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarac <ysarac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:33:38 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/06/14 09:08:18 by ysarac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

static int	line_read(t_main *shell)
{
	shell->cmd_line = readline(shell->prompt);
	if (!shell->cmd_line)
		return (clear_history(), perror("Readline"), 2);
	else if (!is_space(shell->cmd_line))
		return (free(shell->cmd_line), 0);
	add_history(shell->cmd_line);
	return (1);
}

void	start_shell(t_main *shell)
{
	int i;
	//t_tokens *t;
	while(1)
	{
		i = line_read(shell);
		if (!i)
			continue ;
		else if (i == 2)
			break;
 		if (!lexer(shell))
			break;
 		/* if (!expender(shell))
			break; */
		//printf("\n");
/* 		t = shell->token;
		while(t)
		{
			printf("-%s-\n", t->value);
			t = t->next;
		}
		printf("\n"); */
 		/* if (!parser(shell, shell->token, 0))
			break;
		if (!executor(shell))
			break; */
		//update veya free?
		shell->control = 1;
	}

}
