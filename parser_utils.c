/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:33:31 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/05/23 11:33:31 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"
#include <stdlib.h>

int	need_remove(char *s)
{
	size_t	i;

	i = 0;
	while(s[i])
	{
		if (!is_whitespace(s[i++]))
			return (0);
	}
	return (1);
}

void	remove_quotes(t_tokens **token)
{
	t_tokens	*tmp;
	t_tokens	*prev;
	t_tokens	*current;

	current = *token;
	prev = NULL;
	while (current)
	{
		if (need_remove(current->value) || (current->is_expend == NONE &&
			(current->type == QUOTE || current->type == D_QUOTE)))
		{
			tmp = current;
			if (prev)
				prev->next = current->next;
			else
				*token = current->next;
			current = current->next;
			free(tmp->value);
			free(tmp);
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
}
