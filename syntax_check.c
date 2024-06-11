/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:30:36 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/05/20 16:11:47 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"
#include "42-libft/libft.h"
#include <unistd.h>

static void	syntax_message(int flag)
{
	if (flag == 1)
		ft_putstr_fd("Syntax error near unexpected pipe token\n", 2);
	else if (flag == 2)
		ft_putstr_fd("Syntax error near unexpected redirection token\n", 2);
	else if (flag == 3)
		ft_putstr_fd("Syntax error unclosed quote.\n", 2);
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

static int	is_rdr_flag(t_tokens *t)
{
	if (t->type == RDR_D_IN || t->type == RDR_IN
		|| t->type == RDR_OUT || t->type == HEREDOC)
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
	size_t	len;
	size_t	len2;

	t = shell->token;
	len = t_lst_size(t);
	len2 = len;
	if (!quote_check(t))
		return (syntax_message(3), 0);
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
