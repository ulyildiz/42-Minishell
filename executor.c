/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t>+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:33:54 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/05/24 21:08:54 by ysarac	          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"
#include "42-libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

static void official_executer(t_command *cmds, t_main *shell, int i, int in_fd, int out_fd)
{
	cmds->pid = fork();
	if (cmds->pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (cmds->pid == 0)
	{
		if (in_fd != STDIN_FILENO)
		{
			dup2(in_fd, STDIN_FILENO);
			close(in_fd);
		}
		if (out_fd != STDOUT_FILENO)
		{
			dup2(out_fd, STDOUT_FILENO);
			close(out_fd);
		}
		execve(cmds->cmd_and_path, cmds->value, shell->env_for_execve_function);
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

int executor(t_main *shell)
{
	int i = 0;
	int in_fd = STDIN_FILENO;
	int pipefd[2];
	t_command *cmds = shell->cmd;

	while (cmds)
	{
		if (cmds->next)
		{
			if (pipe(pipefd) == -1)
			{
				perror("pipe");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			pipefd[1] = STDOUT_FILENO;
		}

		if (is_builtin(cmds, shell))
		{
			// Handle built-in command
			// Implement your built-in command handling logic here
		}
		else if (accessibility(cmds, shell))
		{
			official_executer(cmds, shell, i, in_fd, pipefd[1]);
		}
		else
		{
			ft_putstr_fd("ft_sh: command not found: ", 2);
			ft_putstr_fd(cmds->value[0], 2);
			ft_putchar_fd('\n', 2);
			return 2;
		}
		if (pipefd[1] != STDOUT_FILENO)
			close(pipefd[1]);
		if (in_fd != STDIN_FILENO)
			close(in_fd);
		in_fd = pipefd[0];

		waitpid(cmds->pid, NULL, 0);
		i++;
		cmds = cmds->next;
	}

	return 1;
}
