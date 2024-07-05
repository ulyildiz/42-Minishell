/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:44:12 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/07/04 17:57:57 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"
#include <readline/readline.h>

/* char	*heredoc_expander(char *str, t_main *shell)
{
	char	*tmp;
	size_t	i;
	size_t  start;

	i = 0;
	tmp = ft_strdup("");
	if(!tmp)
		return (NULL);
	while (str[i] != '\0' && tmp)
	{
		if(str[i] == '$')
			tmp = handle_dollar_sign(tmp, str, &i, shell);
		start = i;
		tmp = append_literal(tmp, str, &start, &i);
		
		i++;
	}
	free(str);
	return (tmp);
} */
// close_all();

int	here_loop(t_main *shell, int *fd, t_command *cmd, char *delimeter)
{
	char	*line;

	cmd->pid = fork();
	if (cmd->pid == -1)
		return (perror("fork"), exit(EXIT_FAILURE), 0);
	else if (cmd->pid == 0)
	{
		signal_reciever(4);
		close(fd[0]);
		close_all(shell->cmd, -1);
		while (1)
		{
			line = readline("> ");
			if (!line)
			{
				close(fd[1]);
				shell->exit_status = 0;
				exit_for_fork(shell);
			}
			if (!ft_strncmp(line, delimeter, ft_strlen(line))
				&& !ft_strncmp(line, delimeter, ft_strlen(delimeter)))
			{
				free(line);
				close(fd[1]);
				shell->exit_status = 0;
				exit_for_fork(shell);
			}
			//line = heredoc_expander(line, shell);
			if (!line)
			{
				shell->exit_status = 1;
				exit_for_fork(shell);
			}	
			ft_putendl_fd(line, fd[1]);
			free(line);
		}
	}
	else
		close(fd[1]);
	return (1);
}

int	wait_heredoc(t_main *shell, t_command *cmd)
{
	int	status;

	waitpid(cmd->pid, &status, 0);
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 1)
			return (shell->exit_status = 1, SIGINT);
		else
			shell->exit_status = WEXITSTATUS(status);
	}
	while (wait(NULL) != -1)
		;
	return (0);
}

int	check_heredoc(t_command *cmd)
{
	int	i;
	int	j;
	int	k;

	k = 0;
	while (cmd)
	{
		i = -1;
		while (cmd->rdrs && cmd->rdrs[++i])
		{
			if (!ft_strncmp(cmd->rdrs[i], "<<", 2))
			{
				j = i + 1;
				if (!cmd->rdrs[j])
					return (0);
				k++;
			}
		}
		cmd = cmd->next;
	}
	if (k == 0)
		return (0);
	return (1);
}

int	heredocs(t_main *shell, t_command *cmd)
{
	int	fd[2];
	int	i;

	if (check_heredoc(cmd) == 0)
		return (1);
	signal_reciever(5);
	i = 0;
	while (cmd)
	{
		i = -1;
		while (cmd->rdrs && cmd->rdrs[++i])
		{
			if (!ft_strncmp(cmd->rdrs[i], "<<", 2))
			{
				if (pipe(fd) == -1)
					return (0);
				here_loop(shell, fd, cmd, cmd->rdrs[++i]);
				if (wait_heredoc(shell, cmd) == SIGINT)
					return (0);
				if (cmd->fd[0] != STDIN_FILENO)
					close(cmd->fd[0]);
				cmd->fd[0] = fd[0];
			}
		}
		cmd->pid = -1;
		cmd = cmd->next;
	}
	return (1);
}
