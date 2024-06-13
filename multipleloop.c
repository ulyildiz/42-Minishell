/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:33:54 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/05/29 00:23:49 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"
#include "42-libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

 // "| cat" seg fault
void	exec(t_command *cmd, t_main *shell, int *fd)
{
	
}

void	set_fd(int *fd, t_command *cmd)
{
	if (cmd->where_r == L_RDR_IN || cmd->where_r == L_RDR_OUT)
		;
	else if (cmd->where_p == R_P || cmd->where_p == B_P)
	{
		if (pipe(fd) == -1)
			return ;
		cmd->fd[1] = fd[1];
		cmd->next->fd[0] = fd[0];
	}
	else
		cmd->fd[1] = STDOUT_FILENO;
}

static void official_executer(t_command *cmds, t_main *shell, int i)
{

	cmds->pid = fork();
	if (cmds->pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (cmds->pid == 0)
	{
		if (i == 0 && cmds->fd[1] != STDOUT_FILENO)
		{
			dup2(cmds->fd[1], 1);
		}
		else if (i > 0 && cmds->next)
		{
			close(cmds->prev->fd[1]);
			dup2(cmds->fd[0], 0);
			dup2(cmds->fd[1], 1);
		}
		else if (i > 0)
		{
			close(cmds->prev->fd[1]);
			dup2(cmds->fd[0], 0);
			dup2(cmds->fd[1], 1);
		}
		execve(cmds->cmd_and_path, cmds->value, shell->env_for_execve_function);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	waitpid(cmds->pid, NULL, 0);
}
int executor(t_main *shell)
{
	int fd[2];
	t_command *cmds;
	int i = 0;

	if (shell->control == 0)
		return (0);
	cmds = shell->cmd;
	shell->paths = get_cmd(shell->envs);
	if (!shell->paths)
		return (0);
	while (cmds)
	{
		if (cmds->where_p != NONE_P || cmds->where_r != NONE_RDR)
			set_fd(fd, cmds); // fd ayarlama
		if (is_builtin(cmds, shell))
			;
		else if (accessibility(cmds, shell))
			official_executer(cmds, shell, i);
		else
			return (ft_putstr_fd("ft_sh: command not found: ", 2), ft_putstr_fd(cmds->value[0], 2),
				ft_putchar_fd('\n', 2), free_double(shell->paths), 2);
		if (cmds->fd[1] != STDOUT_FILENO)
			close(cmds->fd[1]);
		if (cmds->prev && cmds->prev->fd[0] != STDIN_FILENO)
			close(cmds->prev->fd[0]);
		i++;
		cmds = cmds->next;
	}
	return (free_double(shell->paths), 1);
}
