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

void	for_prev(t_command *cmds, t_token_types type)
{
	if (cmds->where_p == L_P && type == PIPE)
		cmds->where_p = B_P;
	else if (type == PIPE)
		cmds->where_p = R_P;
	else if (type == RDR_IN)
		cmds->where_r = R_RDR_IN;
	else if (type == RDR_D_IN)
		cmds->where_r = R_D_RDR_IN;
	else if (type == RDR_OUT)
		cmds->where_r = R_RDR_OUT;
	else if (type == HEREDOC)
		cmds->where_r = R_RDR_H;
}

void	for_itself(t_command *cmds, t_token_types type)
{
	if (type == PIPE)
		cmds->where_p = L_P;
	else if (type == RDR_IN)
		cmds->where_r = L_RDR_IN;
	else if (type == RDR_D_IN)
		cmds->where_r = L_D_RDR_IN;
	else if (type == RDR_OUT)
		cmds->where_r = L_RDR_OUT;
	else if (type == HEREDOC)
		cmds->where_r = L_RDR_H;
}
