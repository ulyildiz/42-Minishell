/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:44:12 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/07/21 11:26:31 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"
#include "libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <unistd.h>
#include <sys/wait.h>

static char	*heredoc_expander(char *str, t_main *shell)
{
	size_t	i;
	size_t	start;
	char	*tmp;

	i = 0;
	tmp = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$')
			tmp = handle_dollar_sign(tmp, str, &i, shell);
		else
		{
			start = i;
			while (str[i] && str[i] != '$')
				i++;
			tmp = append_literal(tmp, str, &start, &i);
		}
		if (!tmp)
			return (perror("Dollar Expend"), NULL);
	}
	free(str);
	return (tmp);
}

static void	here_in(t_main *shell, int *fd, char *delimeter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || (!ft_strncmp(line, delimeter, ft_strlen(line)) \
		&& !ft_strncmp(line, delimeter, ft_strlen(delimeter))))
		{
			if (line)
				free(line);
			close(fd[1]);
			shell->es = 0;
			exit_in_parser(shell, 1);
		}
		line = heredoc_expander(line, shell);
		if (!line)
		{
			shell->es = 1;
			close(fd[1]); // parentanda çıkmalı mı
			exit_in_parser(shell, 1);
		}
		ft_putendl_fd(line, fd[1]);
		free(line);
	}
}

static int	wait_heredoc(t_main *shell, t_command *cmd)
{
	int	status;

	waitpid(cmd->pid, &status, 0);
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 1)
			return (shell->es = 1, SIGINT);
		else
			shell->es = WEXITSTATUS(status);
	}
	while (wait(NULL) != -1)
		;
	return (0);
}

static int	here_loop(t_main *shell, int *fd, t_command *cmd, char *delimeter)
{
	cmd->pid = fork();
	if (cmd->pid == -1)
		return (shell->es = 1, exit_in_parser(shell, 0), 0);
	else if (cmd->pid == 0)
	{
		signal_reciever(4);
		close(fd[0]);
		here_in(shell, fd, delimeter);
	}
	else
	{
		close(fd[1]);
		if (wait_heredoc(shell, cmd) == SIGINT)
			return (close(fd[0]), SIGINT);
		cmd->here_fd = fd[0];
	}
	return (1);
}

int	heredocs(t_main *shell, t_command *cmd)
{
	int	fd[2];
	int	i;

	if (check_heredoc(cmd) == 0)
		return (1);
	signal_reciever(5);
	while (cmd)
	{
		i = -1;
		while (cmd->rdrs && cmd->rdrs[++i])
		{
			if (!ft_strncmp(cmd->rdrs[i], "<<", 2))
			{
				if (pipe(fd) == -1)
					return (exit_in_parser(shell, 0), 0);
				if (here_loop(shell, fd, cmd, cmd->rdrs[++i]) == SIGINT)
					return (signal_reciever(1), 0);
			}
		}
		cmd->pid = -1;
		cmd = cmd->next;
	}
	signal_reciever(1);
	return (1);
}
