/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 12:50:27 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/07/07 14:59:06 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

void	deletenode(t_command **head, t_command *key_point)
{
	if (!head || !*head || !key_point)
		return ;
	if (*head == key_point)
	{
		*head = key_point->next;
		if (*head)
			(*head)->prev = NULL;
		free_c(key_point);
		return ;
	}
	if (key_point->prev)
		key_point->prev->next = key_point->next;
	if (key_point->next)
		key_point->next->prev = key_point->prev;
	free_c(key_point);
}

int	check_heredoc(t_command *cmd)
{
	int	i;
	int	j;
	int	k;

	k = 0;
	while (cmd)
	{
		i = -1;
		while (cmd->rdrs && cmd->rdrs[++i])
		{
			if (!ft_strncmp(cmd->rdrs[i], "<<", 2))
			{
				j = i + 1;
				if (!cmd->rdrs[j])
					return (0);
				k++;
			}
		}
		cmd = cmd->next;
	}
	if (k == 0)
		return (0);
	return (1);
}
