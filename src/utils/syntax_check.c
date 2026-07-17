/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarac <ysarac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:19:36 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/06/28 12:59:55 by ysarac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

static int	is_rdr_flag(t_tokens *t)
{
	if (t->type == RDR_D_IN || t->type == RDR_IN || t->type == RDR_OUT
		|| t->type == HEREDOC)
		return (1);
	return (0);
}

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

static int	rdr_check(t_tokens *t, size_t len)
{
	if (!is_rdr_flag(t))
		return (1);
	if (t->next == NULL)
		return (0);
	else if (t->next->type == PIPE)
		return (0);
	else if (is_rdr_flag(t->next))
		return (0);
	else if (len == 0 && t->next == NULL)
		return (0);
	return (1);
}

static int	quote_check(t_tokens *t, t_bool in_s, t_bool in_d)
{
	size_t	d_c;
	size_t	s_c;
	size_t	i;

	i = 0;
	d_c = 0;
	s_c = 0;
	while (t->value[i])
	{
		if (t->value[i] == '\'' && !in_d)
		{
			s_c++;
			in_s = !in_s;
		}
		if (t->value[i] == '"' && !in_s)
		{
			d_c++;
			in_d = !in_d;
		}
		i++;
	}
	if (d_c % 2 != 0 || s_c % 2 != 0)
		return (0);
	return (1);
}

int	token_check(t_main *shell)
{
	t_tokens	*t;
	size_t		len;
	size_t		len2;

	if (!quote_check(shell->token, FALSE, FALSE))
		return (syntax_message(3), 0);
	t = shell->token;
	len = t_lst_size(t);
	len2 = len;
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
