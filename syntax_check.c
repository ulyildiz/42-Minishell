/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarac <ysarac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:30:36 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/05/21 14:07:15 by ysarac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"
#include "42-libft/libft.h"
#include <unistd.h>

static int	pipe_check(t_tokens *t)
{
	if (t->type == PIPE && t->next == NULL)
		return (write(2, "s", 1), 0);
	else if (t->type == CMD && ft_strnstr(t->value, "|", ft_strlen(t->value)))
		return (write(2, "d", 1), 0);
	else if (t->type == PIPE && (t->next->type == HEREDOC
			|| t->next->type == RDR_IN || t->next->type == RDR_OUT
			|| t->next->type == PIPE))
		return (write(2, "a", 1), 0);
	return (1);
}
//  '<>' '><' düşün
static int	rdr_check(t_tokens *t)
{
	if ((t->type == RDR_IN || t->type == RDR_OUT
			|| t->type == HEREDOC) && t->next == NULL)
		return (0);
	else if (t->next && ((t->type == HEREDOC || t->type == RDR_IN || t->type == RDR_OUT)
		&& (t->next->type == HEREDOC || t->next->type == RDR_IN
		|| t->next->type == RDR_OUT)))
		return (0);
	else if ((t->type == HEREDOC || t->type == RDR_IN
			|| t->type == RDR_OUT) && t->next->type == PIPE)
		return (0);
	return (1);
}

int	token_check(t_tokens *token)
{
	t_tokens	*t;

	t = token;
	while (t)
	{
		if (!pipe_check(t))
			return (ft_putstr_fd(
					"Syntax error near unexpected pipe token\n", 2), 0);
		else if (!rdr_check(t))
			return (ft_putstr_fd(
					"Syntax error near unexpected redirection token\n", 2), 0);
		t = t->next;
	}
	return (1);
}
