/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 12:49:03 by ysarac            #+#    #+#             */
/*   Updated: 2024/06/29 08:08:25 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"
#include <errno.h>
#include <sys/stat.h>


int	accessibility(t_command *cmds, t_main *shell)
{
	size_t	i;
	char	*tmp;
	struct stat	buf;

		
	i = 0;
	cmds->cmd_and_path = NULL;
	if (access(cmds->value[0], F_OK) != 0)
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
		write(2, "minishell: \n", 11);
		cmds->cmd_and_path = ft_strdup(cmds->value[0]);
		return (1);
	}
	return (perror("a"), 0);
}

/* void	close_fd(t_command *cmds, int flag)
{
	if (!cmds)
		return ;
} */
