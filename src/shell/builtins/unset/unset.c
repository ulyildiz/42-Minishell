/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:58:29 by ysarac            #+#    #+#             */
/*   Updated: 2024/07/07 12:25:39 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

static void	deletenode(t_env **head, char *key)
{
	t_env	*temp;
	t_env	*prev;

	temp = *head;
	prev = NULL;
	if (temp != NULL && ft_strncmp(temp->name, key, strlen(key)) == 0)
	{
		*head = temp->next;
		free(temp->name);
		free(temp->value);
		free(temp);
		return ;
	}
	while (temp != NULL && ft_strncmp(temp->name, key, strlen(key)) != 0)
	{
		prev = temp;
		temp = temp->next;
	}
	if (temp == NULL)
		return ;
	prev->next = temp->next;
	free(temp->name);
	free(temp->value);
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