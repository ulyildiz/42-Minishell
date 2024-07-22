/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:39:17 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/07/22 16:52:50 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"
#include "libft.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

static int	redirection_touch(t_main *shell, t_command **cmd)
{
	size_t		i;

	i = 0;
	while ((*cmd)->rdrs[i])
	{
		if (opens(*cmd, &i, -1) == -1)
		{
			(*cmd)->in_work = 0;
			shell->es = 1;
			*cmd = (*cmd)->next;
			return (0);
		}
		i++;
	}
	return (1);
}

static void	set_fd(t_main *shell, t_command *cmd, int *i)
{
	int	fd[2];

	while (cmd)
	{
		if (cmd->where_p == R_P)
		{
			if (pipe(fd) == -1)
				return (shell->es = 1, exit_in_exec(shell));
			cmd->fd[1] = fd[1];
			cmd->next->fd[0] = fd[0];
		}
		(*i)++;
		if (cmd->in_work)
		{
			if (cmd->rdrs)
			{
				if (!redirection_touch(shell, &cmd))
					continue ;
			}
		}
		if (cmd)
			cmd = cmd->next;
	}
}

static void	official_executer(t_command *cmds, t_main *shell, int i,
		t_bool cmd_num)
{
	if (!cmd_num)
		cmds->pid = fork();
	if (cmds->pid == -1)
	{
		perror("Fork");
		shell->es = 1;
		exit_for_fork(shell);
	}
	else if (cmds->pid == 0)
	{
		signal_reciever(2);
		dup2(cmds->fd[1], STDOUT_FILENO);
		if (cmds->fd[1] != STDOUT_FILENO)
			close(cmds->fd[1]);
		dup2(cmds->fd[0], STDIN_FILENO);
		if (cmds->fd[0] != STDIN_FILENO)
			close(cmds->fd[0]);
		close_all(cmds->next, i);
		execve(cmds->cmd_and_path, cmds->value, shell->env_for_execve_function);
		perror("Execve");
		shell->es = 1;
		exit_for_fork(shell);
	}
	signal_reciever(3);
}

void	run_command(t_main *shell, t_command *cmds, int i, t_bool cmd_num)
{
	if (cmd_num)
	{
		cmds->pid = fork();
		if (cmds->pid == -1)
		{
			perror("Fork");
			shell->es = 1;
			exit_for_fork(shell);
		}
		else if (cmds->pid != 0)
			return (signal_reciever(3));
		signal_reciever(2);
	}
	if (!is_builtin(cmds, cmd_num, ft_strlower(ft_strdup(cmds->value[0])), -1))
		;
	else if (accessibility(cmds, shell))
		official_executer(cmds, shell, i, cmd_num);
	else
	{
		if (cmd_num)
			exit_for_fork(shell);
	}
}

void	executor(t_main *shell, t_command *cmds, t_bool cmd_num, int i)
{
	if (shell->control == 0)
		return ;
	cmds = shell->cmd;
	shell->paths = get_cmd(shell->envs);
	if (!shell->paths)
		return (shell->es = 12, exit_in_exec(shell));
	set_fd(shell, cmds, &i);
	if (cmds && cmds->next)
		cmd_num = TRUE;
	while (cmds != NULL)
	{
		if (cmds->in_work)
			run_command(shell, cmds, i, cmd_num);
		if (cmds->fd[1] != STDOUT_FILENO)
			close(cmds->fd[1]);
		if (cmds->fd[0] != STDIN_FILENO)
			close(cmds->fd[0]);
		cmds = cmds->next;
	}
	wait_forks(shell, shell->cmd);
	return (free_double(shell->paths), free(shell->cmd_line),
		free_command(shell, NULL));
}
