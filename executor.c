/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:39:17 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/06/24 20:52:41 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42-libft/libft.h"
#include "functions.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static int	opens(t_command *cmd, size_t *i)
{
	int	fd;

	if (!ft_strncmp(cmd->rdrs[*i], ">>", 2))
	{
		fd = open(cmd->rdrs[++(*i)], O_CREAT | O_APPEND | O_WRONLY, 0777);
		if (fd == -1)
			return (perror(cmd->rdrs[(*i)]), -1);
		if (cmd->fd[1] != STDOUT_FILENO)
			close(cmd->fd[1]);
		cmd->fd[1] = fd;
	}
	else if (!ft_strncmp(cmd->rdrs[*i], "<", 1))
	{
		fd = open(cmd->rdrs[++(*i)], O_RDONLY, 0777);
		if (fd == -1)
			return (perror(cmd->rdrs[(*i)]), -1);
		if (cmd->fd[0] != STDIN_FILENO)
			close(cmd->fd[0]);
		cmd->fd[0] = fd;
	}
	else if (!ft_strncmp(cmd->rdrs[*i], ">", 1))
	{
		fd = open(cmd->rdrs[++(*i)], O_CREAT | O_TRUNC | O_WRONLY, 0777);
		if (fd == -1)
			return (perror(cmd->rdrs[(*i)]), -1);
		if (cmd->fd[1] != STDOUT_FILENO)
			close(cmd->fd[1]);
		cmd->fd[1] = fd;
	}
	return (0);
}

static int	redirection_touch(t_command *cmd)
{
	size_t	i;

	i = 0;
	while (cmd->rdrs[i])
	{
		if (opens(cmd, &i) == -1)
			return (0);
		i++;
	}
	return (1);
}

int	set_fd(t_command *cmd, int *i) //fdleri dinamik yapmayı dene
{
	int	fd[2];

	while (cmd)
	{
		if (cmd->where_p == R_P)
		{
			if (pipe(fd) == -1)
				return (perror("Pipe"), 1);
			cmd->fd[1] = fd[1];
			cmd->next->fd[0] = fd[0];
		}
		if (cmd->rdrs)
		{
			if (!redirection_touch(cmd))
				return (1);
		}
		(*i)++;
		cmd = cmd->next;
	}
	return (0);
}

void	close_all(t_command *cmds, int i)
{
	int	count;

	count = 0;
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

static void	official_executer(t_command *cmds, t_main *shell, int i, t_bool is_single)
{
	t_command *tmp;

	cmds->pid = fork();
	if (cmds->pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (cmds->pid == 0)
	{
		if (is_single == FALSE)
		{
			dup2(cmds->fd[1], STDOUT_FILENO);
			dup2(cmds->fd[0], STDIN_FILENO);
			tmp = cmds->next;
			close_all(tmp, i);
		}
		execve(cmds->cmd_and_path, cmds->value, shell->env_for_execve_function);
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

int	executor(t_main *shell)
{
	t_command	*cmds;
	int			i;

	cmds = shell->cmd;
	if (shell->control == 0)
		return (1);
	shell->paths = get_cmd(shell->envs);
	if (!shell->paths)
		return (0);
	if (set_fd(cmds, &i))
		return (free_double(shell->paths), close_all(cmds, i), 1);
	while (cmds != NULL)
	{
		if (is_builtin(cmds, shell))
			;
		else if (accessibility(cmds, shell))
			official_executer(cmds, shell, i ,FALSE);
		else
		{
			ft_putstr_fd("ft_sh: command not found: ", 2);
			ft_putstr_fd(cmds->value[0], 2);
			ft_putchar_fd('\n', 2);
		}
		if (cmds->fd[1] != STDOUT_FILENO)
			close(cmds->fd[1]);
		if (cmds->fd[0] != STDIN_FILENO)
			close(cmds->fd[0]);
		cmds = cmds->next;
	}
	while (wait(NULL) != -1)
		;
	return (free_double(shell->paths), /* free_command(shell), */ 1);
}
