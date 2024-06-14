/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarac <ysarac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:33:26 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/06/14 11:12:05 by ysarac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

static int quote_controls(char *key_words)
{
	
}

int lexer(t_main *shell)
{
	int i;
	
	printf("%s\n", shell->cmd_line);
	i = 0;
	while (shell->cmd_line[i])
	{
		if (shell->cmd_line[i] = '"' || shell->cmd_line[i] = '\'' )
		{
			/* code */
		}
			
		i++;
	}	
	return(1);
}