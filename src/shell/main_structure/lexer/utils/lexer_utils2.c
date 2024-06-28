/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 23:10:18 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/06/11 15:11:52 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

void	listing_squote(t_main *shell, char *tmp, size_t *j, char *token)
{
	if (*j > 0)
	{
		tmp[*j] = '\0';
		tlist(&shell->token, tmp);
		*j = 0;
	}
	shell->in_s = !shell->in_s;
	tlist(&shell->token, token);
}

void	listing_dquote(t_main *shell, char *tmp, size_t *j, char *token)
{
	if (*j > 0)
	{
		tmp[*j] = '\0';
		tlist(&shell->token, tmp);
		*j = 0;
	}
	shell->in_d = !shell->in_d;
	tlist(&shell->token, token);
}

void	listing_token(t_main *shell, char *tmp, size_t *j, char *token)
{
	if (*j > 0)
	{
		tmp[*j] = '\0';
		tlist(&shell->token, tmp);
		*j = 0;
	}
	tlist(&shell->token, token);
}

void	listing_rdr(t_main *shell, char *tmp, size_t *j, size_t *i, char *token)
{
	if (*j > 0)
	{
		tmp[*j] = '\0';
		tlist(&shell->token, tmp);
		*j = 0;
	}
	if (token[0] == '>' && shell->cmd_line[*i + 1] == '>')
	{
		tlist(&shell->token, ">>");
		(*i)++;
	}
	else if (token[0] == '<' && shell->cmd_line[*i + 1] == '<')
	{
		tlist(&shell->token, "<<");
		(*i)++;
	}
	else
		tlist(&shell->token, token);
}
