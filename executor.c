/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:33:54 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/06/01 18:37:18 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"
#include "42-libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

/* void	redirection_touch(t_command *cmd, t_command *lst) //?
{
	if (lst->where_r == L_RDR_IN)
		cmd->fd[1] = open(lst->value[0], O_CREAT | O_APPEND | O_WRONLY, 777); // -1 kontrol?
	else if (lst->where_r == L_D_RDR_IN)
		cmd->fd[1] = open(lst->value[0], O_CREAT | O_TRUNC | O_WRONLY, 777);
	else if (lst->where_r == L_RDR_OUT)
		cmd->fd[0] = open(lst->value[0], O_RDONLY);
} */

/* void	set_fd(t_command *cmd, t_command **lst)
{
	int	fd[2];
	
	while ((*lst) && ((*lst)->where_r == R_D_RDR_IN || (*lst)->where_r == R_RDR_IN
		|| (*lst)->where_r == R_RDR_OUT))
	{
		open((*lst)->value[0], O_CREAT);
		(*lst) = (*lst)->next;
	}
	if ((*lst) && (*lst)->where_r == L_D_RDR_IN || (*lst)->where_r == L_RDR_IN
		|| (*lst)->where_r == L_RDR_OUT)
		redirection_touch(cmd, *lst);
	else if (cmd->where_p == R_P || cmd->where_p == B_P)
	{
		if (pipe(fd) == -1)
			return ;
		cmd->fd[1] = fd[1];
		cmd->next->fd[0] = fd[0];
		printf("cmd = %s - fd %d\n", cmd->value[0] ,cmd->fd[1]);
	}
	if (cmd->prev)
			close(cmd->prev->fd[1]);
} */

int	set_fd(t_command *cmd)
{
	int fd[2];
	
	while (cmd)
	{	if (/*rdr*/)
			;
		else if (cmd->where_p == R_P || cmd->where_p == B_P)
		{
			if (pipe(fd) == -1)
				return (0);
			cmd->fd[1] = fd[1];
			cmd->next->fd[0] = fd[0];
		}
		cmd = cmd->next;
	}
	return (1);
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
			dup2(cmds->fd[1], 1);
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
	t_command	*cmds;
	int i = 0;

	cmds = shell->cmd;
	if (shell->control == 0)
		return (0);
	if ((cmds->where_p != NONE_P || cmds->where_r != NONE_RDR)
		&& !set_fd(cmds))
		return (0);
	shell->paths = get_cmd(shell->envs);
	if (!shell->paths)
		return (0); //closela
	while (cmds)
	{
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

/* // Helper function to execute a single command
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
} */
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