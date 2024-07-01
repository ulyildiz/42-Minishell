/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarac <ysarac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 23:10:18 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/07/01 20:19:23 by ysarac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

void	listing_token(t_main *shell, char *tmp, size_t *j, char *token)
{
	if (*j > 0)
	{
		tmp[*j] = '\0';
		if (!tlist(&shell->token, tmp))
			return (free(tmp), exit_in_lex_ex(shell));
		*j = 0;
	}
	if (!tlist(&shell->token, token))
		return (free(tmp), exit_in_lex_ex(shell));
}

void	listing_rdr(t_main *shell, size_t *j, size_t *i, char *token)
{
	if (*j > 0)
	{
		shell->tmp[*j] = '\0';
		if (!tlist(&shell->token, shell->tmp))
			return (free(shell->tmp), exit_in_lex_ex(shell));
		*j = 0;
	}
	if (token[0] == '>' && shell->cmd_line[*i + 1] == '>')
	{
		if (!tlist(&shell->token, ">>"))
			return (free(shell->tmp), exit_in_lex_ex(shell));
		(*i)++;
	}
	else if (token[0] == '<' && shell->cmd_line[*i + 1] == '<')
	{
		if (!tlist(&shell->token, "<<"))
			return (free(shell->tmp), exit_in_lex_ex(shell));
		(*i)++;
	}
	else
	{
		if (!tlist(&shell->token, token))
			return (free(shell->tmp), exit_in_lex_ex(shell));
	}
}
