/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 12:49:03 by ysarac            #+#    #+#             */
/*   Updated: 2024/07/22 16:48:16 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"
#include "libft.h"
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>

void	error_handler(t_command *cmds, int flag, t_main *shell)
{
	ft_putstr_fd("ft_sh: ", 2);
	ft_putstr_fd(cmds->value[0], 2);
	if (flag == 1)
	{
		ft_putendl_fd(": command not found", 2);
		shell->es = 127;
	}
	else if (flag == 2)
	{
		ft_putendl_fd(": No such file or directory", 2);
		shell->es = 127;
	}
	else if (flag == 3)
	{
		ft_putendl_fd(": Permission denied", 2);
		shell->es = 126;
	}
	else if (flag == 4)
	{
		ft_putendl_fd(": is a directory", 2);
		shell->es = 126;
	}
}

static int	check_for_absolute_path(t_command *cmds, t_main *shell,
			t_bool *is_in)
{
	struct stat	buf;

	if (!need_to_be_slash(cmds->value[0]))
		return (0);
	if (stat(cmds->value[0], &buf) == 0)
	{
		if (S_ISDIR(buf.st_mode))
			return (error_handler(cmds, 4, shell), *is_in = TRUE, 0);
		if (access(cmds->value[0], X_OK) != 0)
			return (error_handler(cmds, 3, shell), *is_in = TRUE, 0);
		return (1);
	}
	else
	{
		error_handler(cmds, 2, shell);
		*is_in = TRUE;
	}
	return (0);
}

static int	is_it_dir(char *path, t_main *shell, t_command *cmd)
{
	struct stat	buf;

	if (stat(path, &buf) == 0)
	{
		if (S_ISDIR(buf.st_mode))
			return (error_handler(cmd, 1, shell), 1);
	}
	return (0);
}

static int	is_it_path_command(t_command *cmd, t_main *shell)
{
	char	*tmp;
	size_t	i;

	i = -1;
	tmp = ft_strjoin("/", cmd->value[0]);
	if (!tmp)
		return (0);
	while (shell->paths[++i])
	{
		cmd->cmd_and_path = ft_strjoin(shell->paths[i], tmp);
		if (!cmd->cmd_and_path)
			return (free(tmp), 0);
		if (is_it_dir(cmd->cmd_and_path, shell, cmd))
			return (free(tmp), free(cmd->cmd_and_path),
				cmd->cmd_and_path = NULL, 0);
		if (access(cmd->cmd_and_path, X_OK) == 0)
			return (free(tmp), 1);
		free(cmd->cmd_and_path);
		cmd->cmd_and_path = NULL;
	}
	return (free(tmp), error_handler(cmd, 1, shell), 0);
}

int	accessibility(t_command *cmds, t_main *shell)
{
	t_bool		is_in;

	is_in = FALSE;
	if (cmds && (!cmds->value[0] || !cmds->value[0][0]))
		return (0);
	if (check_for_absolute_path(cmds, shell, &is_in))
	{
		cmds->cmd_and_path = ft_strdup(cmds->value[0]);
		if (!cmds->cmd_and_path)
			return (0);
		return (1);
	}
	else if (is_in == FALSE && is_it_path_command(cmds, shell))
		return (1);
	return (0);
}
