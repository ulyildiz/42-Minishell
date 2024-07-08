/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarac <yunusemresarac@yaani.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:26:15 by ysarac            #+#    #+#             */
/*   Updated: 2024/07/08 16:26:18 by ysarac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

static int	deletenode(t_env **head, char *key)
{
	t_env	*temp;
	t_env	*prev;

	temp = *head;
	prev = NULL;
	if (temp != NULL && ft_strncmp(temp->name, key, ft_strlen(key)) == 0)
	{
		*head = temp->next;
		free(temp->name);
		free(temp->value);
		free(temp);
		return (0);
	}
	while (temp != NULL && ft_strncmp(temp->name, key, ft_strlen(key)) != 0)
	{
		prev = temp;
		temp = temp->next;
	}
	if (temp == NULL)
		return (0);
	prev->next = temp->next;
	free(temp->name);
	free(temp->value);
	free(temp);
	return (1);
}

int	unset(t_command *cmds, t_main *shell)
{
	int	i;

	i = 1;
	while (cmds->value[i] != NULL)
	{
		if (deletenode(&shell->envs, cmds->value[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

// d0nE