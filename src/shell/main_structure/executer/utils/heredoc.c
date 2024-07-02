/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:44:12 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/07/02 20:03:24 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"
#include <readline/readline.h>

/* int	here_loop(int *fd, t_command *cmd, int i)
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
				exit(0);
			
		}
	}
	else
	{
		close(fd[1]);
		waitpid(pid, NULL, 0); // sinyalle çıkarken 1 ile çıkıyor
	}
	return (1);
}

int	heredocs(t_command *cmd)
{
	int	*fd;
	int	i;

	if (!cmd->rdrs)
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
				here_loop(fd, cmd, i);
			}
		}
		cmd = cmd->next;
	}
	return (1);	
} */
