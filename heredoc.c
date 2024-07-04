/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarac <ysarac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:44:12 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/07/04 07:03:48 by ysarac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"
#include <readline/readline.h>

// close_all();

int	here_loop(int *fd, t_command *cmd, char *delimeter)
{
	int		pid;
	char	*line;

	pid = fork();
	if (pid == -1)
		return (perror("fork"), exit(EXIT_FAILURE), 0);
	else if (pid == 0)
	{
		signal_reciever(4);
		close(fd[0]);
		while (1)
		{
			line = readline("> ");
			if (!line)
			{
				close(fd[1]);
				exit(0);
			}
			else if (!ft_strncmp(line, delimeter, ft_strlen(delimeter)))
			{
				free(line);
				close(fd[1]);
				exit(0);
			}
			ft_putendl_fd(line, fd[1]);
			free(line);
		}
	}
	else
	{
		close(fd[1]);
		waitpid(pid, NULL, 0); // sinyalle çıkarken 1 ile çıkıyor
	}
	return (1);
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

int	heredocs(t_command *cmd)
{
	int	fd[2];
	int	i;

	printf("%p\n", cmd);
	if (check_heredoc(cmd) == 0)
		return (1);
	while (cmd)
	{
		i = -1;
		while (cmd->rdrs[++i])
		{
			if (!ft_strncmp(cmd->rdrs[i], "<<", 2))
			{
				if (pipe(fd) == -1)
					return (0);
				if (cmd->fd[0] != STDIN_FILENO)
					close(cmd->fd[0]);
				here_loop(fd, cmd, cmd->rdrs[++i]);
				cmd->fd[0] = fd[0];
			}
		}
		cmd = cmd->next;
	}
	return (1);
}
