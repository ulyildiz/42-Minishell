/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarac <ysarac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:33:23 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/06/28 13:01:22 by ysarac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

static t_token_types	identify_t(const char *arr)
{
	if (ft_strlen(arr) == 1 && *arr == '|')
		return (PIPE);
	else if (ft_strlen(arr) == 1 && *arr == '<' )
		return (RDR_OUT);
	else if (ft_strlen(arr) == 2 && ft_strnstr(arr, "<<", 2))
		return (HEREDOC);
	else if (ft_strlen(arr) == 2 && ft_strnstr(arr, ">>", 2))
		return (RDR_D_IN);
	else if (ft_strlen(arr) == 1 && *arr == '>')
		return (RDR_IN);
	return (CMD);
}

static int	token_add_back(t_tokens **list, t_tokens *new)
{
	t_tokens	*tmp;

	tmp = *list;
	if (!new)
		return (0);
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	return (1);
}

static t_tokens	*create_token(char	*arr)
{
	t_tokens	*new;

	new = (t_tokens *)ft_calloc(1, sizeof(t_tokens));
	if (!new)
		return (NULL);
	new->value = ft_strdup(arr);
	new->is_expend = NONE;
	new->type = identify_t(arr);
	return (new);
}

int	tlist(t_tokens **head, char *arr)
{
	t_tokens	*new;

	new = create_token(arr);
	if (!new)
		return (0);
	if (!*head)
		*head = new;
	else
		token_add_back(head, new);
	return (1);
}
