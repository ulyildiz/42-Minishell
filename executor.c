/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:33:54 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/06/03 13:10:36 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"
#include "42-libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>

static int	opens(t_command *cmd, t_command *lst, int flag)
{
	int	i;

	i = 0;
	if (lst->prev->where_r == R_RDR_IN || lst->where_r == L_RDR_IN)
		i = open(lst->value[0], O_CREAT | O_TRUNC | O_WRONLY, 0777);
	else if (lst->prev->where_r == R_D_RDR_IN || lst->where_r == L_D_RDR_IN)
		i = open(lst->value[0], O_CREAT | O_APPEND | O_WRONLY, 0777);
	else if (lst->where_r == R_RDR_OUT || lst->where_r == L_RDR_OUT)
		i = open(lst->value[0], O_RDONLY, 0666);
	if (flag == 1)
	{
		if (lst->where_r == L_RDR_IN)
			cmd->fd[1] = i;
		else if (lst->where_r == L_D_RDR_IN)
			cmd->fd[1] = i;
		else if (lst->where_r == L_RDR_OUT)
			cmd->fd[0] = i;
	}
	printf("open = %d\n", i);
	return (i);
}

static int	redirection_touch (t_command *cmd, t_command **lst)
{
	int	i;

	i = 0;
	while ((*lst) && ((*lst)->where_r == R_D_RDR_IN || (*lst)->where_r == R_RDR_IN
		|| (*lst)->where_r == R_RDR_OUT))
	{
		if (opens(cmd, *lst, 0) == -1)
			return (0);
		(*lst) = (*lst)->next;
	}
	if ((*lst) && (*lst)->where_r == L_D_RDR_IN || (*lst)->where_r == L_RDR_IN
		|| (*lst)->where_r == L_RDR_OUT)
	{
		if (opens(cmd, *lst, 1) == -1)
			return (0);
	}
	return (1);
}

static int	set_fd(t_command *cmd)
{
	int			fd[2];
	t_command	*lst;

	while (cmd)
	{
		lst = cmd;
		if (cmd->where_r != NONE_RDR)
		{
			lst = lst->next;
			if (!redirection_touch(cmd, &lst))
				return (perror("While opening a file"), 0);
			cmd = lst;
		}
		else if (cmd->where_p == R_P || cmd->where_p == B_P)
		{
			if (pipe(fd) == -1)
				return (perror("Pipe"), 0);
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
		while (cmds && !(cmds->where_p == L_P || cmds->where_p == B_P))
			cmds = cmds->next;
	}
	return (free_double(shell->paths), free_command(shell->cmd), 1);
}
