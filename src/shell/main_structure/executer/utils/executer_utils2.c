/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:19:53 by ysarac            #+#    #+#             */
/*   Updated: 2024/07/21 13:37:44 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "libft.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>

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

int	opens(t_command *cmd, size_t *i, int fd)
{
	if (!ft_strncmp(cmd->rdrs[*i], ">>", 2))
	{
		fd = open(cmd->rdrs[++(*i)], O_CREAT | O_APPEND | O_WRONLY, 0777);
		if (!check_and_close(cmd, STDOUT_FILENO, fd))
			return (perror(cmd->rdrs[(*i)]), -1);
	}
	else if (!ft_strncmp(cmd->rdrs[*i], "<", ft_strlen(cmd->rdrs[*i])))
	{
		fd = open(cmd->rdrs[++(*i)], O_RDONLY, 0777);
		if (!check_and_close(cmd, STDIN_FILENO, fd))
			return (perror(cmd->rdrs[(*i)]), -1);
	}
	else if (!ft_strncmp(cmd->rdrs[*i], "<<", 2))
	{
		++(*i);
		check_and_close(cmd, STDIN_FILENO, cmd->here_fd);
	}
	else if (!ft_strncmp(cmd->rdrs[*i], ">", 1))
	{
		fd = open(cmd->rdrs[++(*i)], O_TRUNC | O_CREAT | O_WRONLY, 0777);
		if (!check_and_close(cmd, STDOUT_FILENO, fd))
			return (perror(cmd->rdrs[(*i)]), -1);
	}
	return (0);
}

void	wait_forks(t_main *shell, t_command *cmd)
{
	int	status;

	while (cmd && cmd->next)
		cmd = cmd->next;
	if (cmd && cmd->in_work)
	{
		waitpid(cmd->pid, &status, 0);
		if (cmd->pid != -1 && WIFEXITED(status))
			shell->es = WEXITSTATUS(status);
		else if (cmd->pid != -1 && WIFSIGNALED(status))
			shell->es = 128 + WTERMSIG(status);
	}
	while (wait(NULL) != -1)
		;
}

void	close_all(t_command *cmds, int i)
{
	int	count;

	count = 0;
	if (i == -1)
	{
		while (cmds)
		{
			if (cmds->fd[1] != STDOUT_FILENO)
				close(cmds->fd[1]);
			if (cmds->fd[0] != STDIN_FILENO)
				close(cmds->fd[0]);
			cmds = cmds->next;
		}
		return ;
	}
	while (cmds && i > count)
	{
		if (cmds->fd[1] != STDOUT_FILENO)
			close(cmds->fd[1]);
		if (cmds->fd[0] != STDIN_FILENO)
			close(cmds->fd[0]);
		count++;
		cmds = cmds->next;
	}
}

int	need_to_be_slash(char *value)
{
	size_t	i;

	i = -1;
	while (value[++i])
		if (value[i] == '/')
			return (1);
	return (0);
}
