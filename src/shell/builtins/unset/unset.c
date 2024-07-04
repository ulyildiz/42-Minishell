/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarac <ysarac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:58:29 by ysarac            #+#    #+#             */
/*   Updated: 2024/07/03 17:59:14 by ysarac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

void	deletenode(t_env **head, char *key)
{
	t_env	*temp;
	t_env	*prev;

	temp = *head;
	prev = NULL;
	if (temp != NULL && ft_strncmp(temp->name, key, ft_strlen(temp->name)) == 0)
	{
		*head = temp->next;
		return (free(temp));
	}
	while (temp != NULL && ft_strncmp(temp->name, key,
			ft_strlen(temp->name)) != 0)
	{
		prev = temp;
		temp = temp->next;
	}
	if (temp == NULL)
		return ;
	prev->next = temp->next;
	free(temp);
}

void	unset(t_command *cmds, t_main *shell)
{
	int	i;

	i = 1;
	while (cmds->value[i] != NULL)
	{
		deletenode(&shell->envs, cmds->value[i]);
		i++;
	}
}

// d0nE