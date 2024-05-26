/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:33:54 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/05/26 18:34:35 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"
#include "42-libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Helper function to execute a single command
static void official_executer(t_command *cmds, t_main *shell, int in_fd, int out_fd)
{
	cmds->pid = fork();
	if (cmds->pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (cmds->pid == 0)
	{
		// Handle input redirection
		if (in_fd != STDIN_FILENO)
		{
			dup2(in_fd, STDIN_FILENO);
			close(in_fd);
		}
		// Handle output redirection
		if (out_fd != STDOUT_FILENO)
		{
			dup2(out_fd, STDOUT_FILENO);
			close(out_fd);
		}
		execve(cmds->cmd_and_path, cmds->value, shell->env_for_execve_function);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	waitpid(cmds->pid, NULL, 0);
}
 
int executor(t_main *shell)
{
	int in_fd = STDIN_FILENO;
	int pipefd[2];
	t_command *cmds;

	cmds = shell->cmd;
	shell->paths = get_cmd(shell->envs);
	while (cmds)
	{
		if (cmds->where_p != NONE_P || cmds->where_r != NONE_RDR)
			//fd ayarlama;
			;
		if (is_builtin(cmds, shell))
			;
		else if (accessibility(cmds, shell))
			official_executer(cmds, shell, in_fd, STDOUT_FILENO);
		else
			return (ft_putstr_fd("ft_sh: command not found: ", 2), ft_putstr_fd(cmds->value[0], 2),
				ft_putchar_fd('\n', 2), free_double(shell->paths), 2);
		cmds = cmds->next;
	}
	return (free_double(shell->paths), 1);
}

/* 
	int i = 0;
	while (shell->paths[i])
		printf("%s\n", shell->paths[i++]); */

/* 		if (cmds->next)
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
			official_executer(cmds, shell, in_fd, pipefd[1]);
		}
		else
		{
			ft_putstr_fd("ft_sh: command not found: ", 2);
			ft_putstr_fd(cmds->value[0], 2);
			ft_putchar_fd('\n', 2);
			return 2;
		}

		// Close the write-end of the current pipe
		if (pipefd[1] != STDOUT_FILENO)
			close(pipefd[1]);
		// Update the input file descriptor for the next command
		if (in_fd != STDIN_FILENO)
			close(in_fd);
		in_fd = pipefd[0];

		waitpid(cmds->pid, NULL, 0);
		cmds = cmds->next;
	} */