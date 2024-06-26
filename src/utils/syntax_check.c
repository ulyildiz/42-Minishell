/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarac <ysarac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:19:36 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/06/26 12:40:41 by ysarac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

static int	pipe_check(t_tokens *t, size_t len)
{
	if (t->type != PIPE)
		return (1);
	if (t->next == NULL)
		return (0);
	else if (t->next->type == PIPE)
		return (0);
	else if (len == 0 && t->next != NULL)
		return (0);
	return (1);
}

static int	is_rdr_flag(t_tokens *t)
{
	if (t->type == RDR_D_IN || t->type == RDR_IN || t->type == RDR_OUT
		|| t->type == HEREDOC)
		return (1);
	return (0);
}

static int	rdr_check(t_tokens *t, size_t len)
{
	if (!is_rdr_flag(t))
		return (1);
	if (t->next == NULL)
		return (0);
	else if (is_rdr_flag(t->next))
		return (0);
	else if (len == 0 && t->next != NULL)
		return (0);
	return (1);
}

static int	quote_check(t_tokens *t)
{
	size_t	d_q;
	size_t	q;

	d_q = 0;
	q = 0;
	while (t)
	{
		if (t->type == D_QUOTE)
			d_q++;
		else if (t->type == QUOTE)
			q++;
		t = t->next;
	}
	if (d_q % 2 != 0 || q % 2 != 0)
		return (0);
	return (1);
}

int	token_check(t_main *shell)
{
	t_tokens	*t;
	size_t		len;
	size_t		len2;

	if (!quote_check(shell->token))
		return (syntax_message(3), 0);
	t = shell->token;
	len = t_lst_size(t);
	len2 = len;
	remove_quotes(&shell->token);
	while (t)
	{
		if (!pipe_check(t, len - len2))
			return (syntax_message(1), 0);
		else if (!rdr_check(t, len - len2))
			return (syntax_message(2), 0);
		len2--;
		t = t->next;
	}
	return (1);
}

// = syntax düzelt