/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 12:49:03 by ysarac            #+#    #+#             */
/*   Updated: 2024/06/28 16:59:15 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

int	accessibility(t_command *cmds, t_main *shell)
{
	size_t	i;
	char	*tmp;

	i = 0;
	if (access(cmds->value[0], X_OK) != 0)
	{
		tmp = ft_strjoin("/", cmds->value[0]);
		if (!tmp)
			return (perror("Access"), 0);
		while (shell->paths[i])
		{
			cmds->cmd_and_path = ft_strjoin(shell->paths[i], tmp);
			if (access(cmds->cmd_and_path, X_OK) == 0)
				return (free(tmp), 1);
			free(cmds->cmd_and_path);
			i++;
		}
		free(tmp);
	}
	else
	{
		cmds->cmd_and_path = ft_strdup(cmds->value[0]);
		return (1);
	}
	return (0);
}

void	close_fd(t_command *cmds, int flag)
{
	if (!cmds)
		return ;
}
