/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:33:28 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/05/23 11:33:28 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "functions.h"
#include "42-libft/libft.h"

int	main(int ac, char **av, char **env)
{
	t_main	shell;

	av = (void *)av;
	if (ac >= 2)
		return (ft_putstr_fd("Too much argument.\n", 2), 1);
	if (!initialize(&shell, env))
		return (perror("Initialize"), 1);
	start_shell(&shell);
	return (0);
}

	//main_free(&shell);
/* 	shell.cmd = NULL;
	shell.cmd_line = NULL;
	shell.envs = NULL;
	shell.paths = NULL;
	shell.prompt = NULL;
	shell.token = NULL;
	system("Leaks minishell"); */