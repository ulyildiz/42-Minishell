/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 23:10:18 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/06/29 11:35:32 by ulyildiz         ###   ########.fr       */
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

void	listing_rdr(t_main *shell, char *tmp, size_t *j, size_t *i, char *token)
{
	if (*j > 0)
	{
		tmp[*j] = '\0';
		if (!tlist(&shell->token, tmp))
			return (free(tmp), exit_in_lex_ex(shell));
		*j = 0;
	}
	if (token[0] == '>' && shell->cmd_line[*i + 1] == '>')
	{
		if (!tlist(&shell->token, ">>"))
			return (free(tmp), exit_in_lex_ex(shell));
		(*i)++;
	}
	else if (token[0] == '<' && shell->cmd_line[*i + 1] == '<')
	{
		if (!tlist(&shell->token, "<<"))
			return (free(tmp), exit_in_lex_ex(shell));
		(*i)++;
	}
	else
	{
		if (!tlist(&shell->token, token))
			return (free(tmp), exit_in_lex_ex(shell));
	}
}
