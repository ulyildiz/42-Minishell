/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarac <ysarac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 07:07:22 by ysarac            #+#    #+#             */
/*   Updated: 2024/07/04 07:07:22 by ysarac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

void	parent_sigint(int sig)
{
	(void)sig;
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	parent_sigint2(int sig)
{
	(void)sig;
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	disable_echo_control_chars(void)
{
	struct termios	tty;

	tcgetattr(STDIN_FILENO, &tty);
	tty.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

void	heredoc_sigint(int sig)
{
	(void)sig;
	ft_putchar_fd('\n', 1);
	exit_for_fork(shell_keeper(NULL));
}

void	signal_reciever(int flag)
{
	if (flag == 1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, parent_sigint);
	}
	else if (flag == 2)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
	}
	else if (flag == 3)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, parent_sigint2);
	}
	else if (flag == 4)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, heredoc_sigint);
	}
}
