/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarac <ysarac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:39:17 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/07/04 15:25:35 by ysarac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

void	free_c(t_command *c)
{
	if (c->cmd_and_path)
		free(c->cmd_and_path);
	if (c->value)
		free_double(c->value);
	if (c->rdrs)
		free_double(c->rdrs);
	free(c);
}

static void	deletenode(t_command **head, t_command *key_point)
{
	if (!head || !*head || !key_point)
		return ;
	if (*head == key_point)
	{
		*head = key_point->next;
		if (*head)
			(*head)->prev = NULL;
		free_c(key_point);
		return ;
	}
	if (key_point->prev)
		key_point->prev->next = key_point->next;
	if (key_point->next)
		key_point->next->prev = key_point->prev;
	free_c(key_point);
}

static int	redirection_touch(t_main *shell, t_command **cmd)
{
	size_t		i;
	t_command	*tmp;

	i = 0;
	tmp = NULL;
	while ((*cmd)->rdrs[i])
	{
		tmp = *cmd;
		if (opens(*cmd, &i) == -1)
		{
			*cmd = (*cmd)->next;
			deletenode(&shell->cmd, tmp);
			return (0);
		}
		i++;
	}
	return (1);
}

int	set_fd(t_main *shell, t_command *cmd, int *i)
{
	int	fd[2];

	if (!heredocs(shell, cmd))
		return (1);
	signal_reciever(1);
	while (cmd)
	{
		if (cmd->where_p == R_P)
		{
			if (pipe(fd) == -1)
				return (perror("Pipe"), 1);
			cmd->fd[1] = fd[1];
			if (cmd->next)
				cmd->next->fd[0] = fd[0];
		}
		if (cmd->rdrs)
		{
			if (!redirection_touch(shell, &cmd))
				return (0);
		}
		(*i)++;
		if (cmd)
			cmd = cmd->next;
	}
	return (0);
}

// Neleri freelememiz lazım eğer fork
// başarısız olursa. parent mi giriyor child mi
static void	official_executer(t_command *cmds, t_main *shell, int i,
		t_bool cmd_num)
{
	t_command	*tmp;

	if (!cmd_num)
		cmds->pid = fork();
	if (cmds->pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (cmds->pid == 0)
	{
		signal_reciever(2);
		rl_clear_history();
		dup2(cmds->fd[1], STDOUT_FILENO);
		if (cmds->fd[1] != STDOUT_FILENO)
			close(cmds->fd[1]);
		dup2(cmds->fd[0], STDIN_FILENO);
		if (cmds->fd[0] != STDIN_FILENO)
			close(cmds->fd[0]);
		tmp = cmds->next;
		close_all(tmp, i);
		execve(cmds->cmd_and_path, cmds->value, shell->env_for_execve_function);
		perror("execve");
		shell->exit_status = 1;
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
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (cmds->pid != 0)
			return (signal_reciever(3));
		signal_reciever(2);
	}
	if (!is_builtin(cmds, shell, cmd_num))
		;
	else if (accessibility(cmds, shell))
		official_executer(cmds, shell, i, cmd_num);
	else
	{
		if (cmd_num)
			exit_for_fork(shell);
	}
}

int	executor(t_main *shell, t_command *cmds, t_bool cmd_num, int i)
{
	i = 0;
	cmds = shell->cmd;
	if (shell->control == 0)
		return (1);
	shell->paths = get_cmd(shell->envs);
	if (!shell->paths)
		return (0);
	if (set_fd(shell, cmds, &i))
		return (free_double(shell->paths), close_all(cmds, i), free(shell->cmd_line), free_command(shell, NULL), 1);
	cmds = shell->cmd;
	if (cmds && cmds->next)
		cmd_num = TRUE;
	while (cmds != NULL)
	{
		run_command(shell, cmds, i, cmd_num);
		if (cmds->fd[1] != STDOUT_FILENO)
			close(cmds->fd[1]);
		if (cmds->fd[0] != STDIN_FILENO)
			close(cmds->fd[0]);
		cmds = cmds->next;
	}
	wait_forks(shell, shell->cmd);
	return (free_double(shell->paths), free(shell->cmd_line),
		free_command(shell, NULL), 1);
}
