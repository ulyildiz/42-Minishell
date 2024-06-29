/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 06:33:08 by ysarac            #+#    #+#             */
/*   Updated: 2024/06/29 06:13:38 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

int	main(int ac, char **av, char **env)
{
	t_main	shell;

	signal_reciever(1);
	disable_echo_control_chars();
	av = (void *)av;
	if (ac >= 2)
		return (ft_putendl_fd("Too much argument.", 2), 1);
	if (!initialize(&shell, env))
		return (perror("Initialize"), 1);
	start_shell(&shell);
	return (0);
}
