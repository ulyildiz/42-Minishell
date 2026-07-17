/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 23:10:18 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/07/22 16:18:50 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"
#include <stdlib.h>

void	listing_token(t_main *shell, char *tmp, size_t *j, char *token)
{
	if (*j > 0)
	{
		tmp[*j] = '\0';
		if (!tlist(&shell->token, tmp))
			return (free(tmp), shell->es = 12, exit_in_lex(shell));
		*j = 0;
	}
	if (!tlist(&shell->token, token))
		return (free(tmp), shell->es = 12, exit_in_lex(shell));
}

void	listing_rdr(t_main *shell, size_t *j, size_t *i, char *token)
{
	if (*j > 0)
	{
		shell->tmp[*j] = '\0';
		if (!tlist(&shell->token, shell->tmp))
			return (free(shell->tmp), shell->es = 12, exit_in_lex(shell));
		*j = 0;
	}
	if (token[0] == '>' && shell->cmd_line[*i + 1] == '>')
	{
		if (!tlist(&shell->token, ">>"))
			return (free(shell->tmp), shell->es = 12, exit_in_lex(shell));
		(*i)++;
	}
	else if (token[0] == '<' && shell->cmd_line[*i + 1] == '<')
	{
		if (!tlist(&shell->token, "<<"))
			return (free(shell->tmp), shell->es = 12, exit_in_lex(shell));
		(*i)++;
	}
	else
	{
		if (!tlist(&shell->token, token))
			return (free(shell->tmp), shell->es = 12, exit_in_lex(shell));
	}
}
