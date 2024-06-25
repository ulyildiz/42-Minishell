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
#include "42-libft/libft.h"
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
			//tmp = NULL; //?
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
}

int	is_token(t_tokens *t)
{
	if (t->type == PIPE && (t->is_expend != WITHIN_D_Q
			&& t->is_expend != WITHIN_Q))
		return (1);
	return (0);
}

size_t	rdr_count(char **str)
{
	size_t	len;
	size_t	i;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (!ft_strncmp(str[i], "<", 1) && ft_strlen(str[i]) == 1)
			len++;
		else if (!ft_strncmp(str[i], ">", 1) && ft_strlen(str[i]) == 1)
			len++;
		else if (!ft_strncmp(str[i], ">>", 2) && ft_strlen(str[i]) == 2)
			len++;
		i++;
	}
	len *= 2;
	return (len);
}

int	is_rdr(char *strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		if (strs[i] == '<')
			return (1);
		if (strs[i] == '>')
			return (1);
		i++;
	}
	return (0);
}
