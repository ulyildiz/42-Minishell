/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarac <ysarac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:19:53 by ysarac            #+#    #+#             */
/*   Updated: 2024/07/01 14:30:20 by ysarac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

static int	check_and_close(t_command *cmd, int fd, int i)
{
	if (i == -1)
		return (0);
	if (fd == STDIN_FILENO)
	{
		if (cmd->fd[0] != STDIN_FILENO)
			close(cmd->fd[0]);
		cmd->fd[0] = i;
	}
	else if (fd == STDOUT_FILENO)
	{
		if (cmd->fd[1] != STDOUT_FILENO)
			close(cmd->fd[1]);
		cmd->fd[1] = i;
	}
	return (1);
}

int	opens(t_command *cmd, size_t *i)
{
	int	fd;

	if (!ft_strncmp(cmd->rdrs[*i], ">>", 2))
	{
		fd = open(cmd->rdrs[++(*i)], O_CREAT | O_APPEND | O_WRONLY, 0777);
		if (!check_and_close(cmd, STDOUT_FILENO, fd))
			return (perror(cmd->rdrs[(*i)]), cmd->ifo++, -1);
	}
	else if (!ft_strncmp(cmd->rdrs[*i], "<", 1))
	{
		fd = open(cmd->rdrs[++(*i)], O_RDONLY, 0777);
		if (!check_and_close(cmd, STDIN_FILENO, fd))
			return (perror(cmd->rdrs[(*i)]), cmd->ifo++, -1);
	}
	else if (!ft_strncmp(cmd->rdrs[*i], ">", 1))
	{
		fd = open(cmd->rdrs[++(*i)], O_TRUNC | O_CREAT | O_WRONLY, 0777);
		if (!check_and_close(cmd, STDOUT_FILENO, fd))
			return (perror(cmd->rdrs[(*i)]), cmd->ifo++, -1);
	}
	return (0);
}
