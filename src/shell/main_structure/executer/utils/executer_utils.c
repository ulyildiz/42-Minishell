/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 12:49:03 by ysarac            #+#    #+#             */
/*   Updated: 2024/06/29 15:01:25 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"
#include <errno.h>
#include <sys/stat.h>

void error_handler(t_command *cmds, int flag)
{
    ft_putstr_fd("ft_sh: ", 2);
    ft_putstr_fd(cmds->value[0], 2);
    if (flag == 1)
        ft_putendl_fd(": command not found", 2);
    else if (flag == 2)
        ft_putendl_fd(": No such file or directory", 2);
    else if (flag == 3)
        ft_putendl_fd(": Permission denied", 2);
    else if (flag == 4)
        ft_putendl_fd(": Is a directory", 2);
}

int accessibility(t_command *cmds, t_main *shell)
{
	size_t		i;
	char		*tmp;
	struct stat	buf;

	i = -1;
	cmds->cmd_and_path = NULL;
	if (access(cmds->value[0], F_OK) != 0)
	{
		if (ft_strchr(cmds->value[0], '/') || cmds->value[0][0] == '.')
			return (error_handler(cmds, 2), 0);
		tmp = ft_strjoin("/", cmds->value[0]);
		if (!tmp)
			return (perror("Access"), 0); //Direkt exit yapılabilir.
		while (shell->paths[++i])
		{
			cmds->cmd_and_path = ft_strjoin(shell->paths[i], tmp);
			if (access(cmds->cmd_and_path, X_OK) == 0)
				return (free(tmp), 1);
			free(cmds->cmd_and_path);
		}
		free(tmp);
	}
	else
	{
		if (stat(cmds->value[0], &buf) == 0)
		{
			if (S_ISDIR(buf.st_mode))
				return (error_handler(cmds, 4), 0);
			if (buf.st_mode & S_IXUSR)
				return (cmds->cmd_and_path = ft_strdup(cmds->value[0]), 1);
			else
				return (error_handler(cmds, 3), 0);
		}
		else
			return (error_handler(cmds, 2), 0);
	}
	return (error_handler(cmds, 1), 0);
}
