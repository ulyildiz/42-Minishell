/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:39:17 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/06/13 12:04:34 by ulyildiz         ###   ########.fr       */
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
		if (cmd->fd[0] != STDOUT_FILENO)
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

int	set_fd(t_command *cmd)
{
	int	fd[2];

	while (cmd)
	{
		if (cmd->where_p == R_P || cmd->where_p == B_P)
		{
			if (pipe(fd) == -1)
				return (perror("pipe"), 0);
			cmd->fd[1] = fd[1];
			cmd->next->fd[0] = fd[0];
		}
		if (cmd->rdrs)
		{
			if (!redirection_touch(cmd))
				return (0);
		}
		cmd = cmd->next;
	}
	return (1);
}

static void	official_executer(t_command *cmds, t_main *shell, int i, t_bool is_single)
{
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
			t_command *tmp = cmds;
			tmp = tmp->next;
			while (tmp)
			{
				if (tmp->fd[0] != STDIN_FILENO)
					close(tmp->fd[0]);
				if (tmp->fd[1] != STDOUT_FILENO)
					close(tmp->fd[1]);
				tmp = tmp->next;
			}
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

	i = 0;
	cmds = shell->cmd;
	if (shell->control == 0)
		return (1);
	shell->paths = get_cmd(shell->envs);
	if (!shell->paths)
		return (0);
	if (!set_fd(cmds))
		return (free_double(shell->paths), 0);
	while (cmds != NULL)
	{
		if (is_builtin(cmds, shell))
			;
		else if (accessibility(cmds, shell))
			official_executer(cmds, shell, i, FALSE);
		else
		{
			if (cmds->fd[1] != STDOUT_FILENO) // kapatıp çıkacaksak tüm pipeler kapnmalı
				close(cmds->fd[1]);
			if (cmds->fd[0] != STDIN_FILENO)
				close(cmds->fd[0]);
			while (wait(NULL) != -1)
				;
			ft_putstr_fd("ft_sh: command not found: ", 2);
			ft_putstr_fd(cmds->value[0], 2);
			ft_putchar_fd('\n', 2);
			free_double(shell->paths);
			return (1); // return atma olmayan komuttan sonraki komutta çalışıyor // gerekli mi?
		}
		if (cmds->fd[1] != STDOUT_FILENO)
			close(cmds->fd[1]);
		if (cmds->fd[0] != STDIN_FILENO)
			close(cmds->fd[0]);
		i++;
		cmds = cmds->next;
	}
	while (wait(NULL) != -1)
	{
		;
	}
	return (free_double(shell->paths), /* free_command(shell->cmd), */ 1);
}

/* 		if (i == 0 && cmds->fd[1] != STDOUT_FILENO)
		{
			dup2(cmds->fd[1], STDOUT_FILENO);
			close(cmds->next->fd[0]);
		}
		else if (i > 0)
		{
			dup2(cmds->fd[1], STDOUT_FILENO);
			close(cmds->prev->fd[1]);
			dup2(cmds->fd[0], STDIN_FILENO);
			close(cmds->fd[0]);
		} */