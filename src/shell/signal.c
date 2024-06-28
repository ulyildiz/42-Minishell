/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:11:28 by ysarac            #+#    #+#             */
/*   Updated: 2024/06/28 21:52:49 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>

void	parent_sigint(int sig)
{
	sig = 0;
	
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
		;
	}
}