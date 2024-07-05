/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarac <ysarac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 19:24:06 by ysarac            #+#    #+#             */
/*   Updated: 2024/07/01 19:31:44 by ysarac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

static void	skip_to_matching_quote(const char *value, size_t *i, char quote)
{
	(*i)++;
	while (value[*i] && value[*i] != quote)
		(*i)++;
	if (value[*i] == quote)
		(*i)++;
}

static size_t	process_token_value(const char *value)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (value[i])
	{
		while (value[i] && is_whitespace(value[i]))
			i++;
		while (value[i] && !is_whitespace(value[i]))
		{
			if (value[i] == '\'')
				skip_to_matching_quote(value, &i, '\'');
			else if (value[i] == '"')
				skip_to_matching_quote(value, &i, '"');
			else
				i++;
		}
		len++;
	}
	return (len);
}

size_t	length_to_token(t_tokens *lst)
{
	size_t	len;

	len = 0;
	while (lst && !is_token(lst))
	{
		len += process_token_value(lst->value);
		lst = lst->next;
	}
	return (len);
}
