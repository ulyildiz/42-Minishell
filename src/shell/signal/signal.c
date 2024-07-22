/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 07:07:22 by ysarac            #+#    #+#             */
/*   Updated: 2024/07/04 17:57:38 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "functions.h"
#include <stdio.h>
#include <readline/readline.h>
#include <termios.h>
#include <unistd.h>
#include <signal.h>

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

	if (!tcgetattr(STDIN_FILENO, &tty))
	{
		tty.c_lflag &= ~ECHOCTL;
		tcsetattr(STDIN_FILENO, TCSANOW, &tty);
	}
}

void	heredoc_sigint(int sig)
{
	(void)sig;
	ft_putchar_fd('\n', 1);
	shell_keeper(NULL)->es = 1;
	exit_in_parser(shell_keeper(NULL), 1);
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
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, heredoc_sigint);
	}
	else if (flag == 5)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
	}
}
