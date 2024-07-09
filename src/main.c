/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 06:33:08 by ysarac            #+#    #+#             */
/*   Updated: 2024/06/29 18:00:08 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"
#include "libft.h"
#include <unistd.h>
#include <stdio.h>

t_main	*shell_keeper(t_main *shell)
{
	static t_main	*shell_keeper;

	if (shell)
		shell_keeper = shell;
	return (shell_keeper);
}

int	main(int ac, char **av, char **env)
{
	t_main	shell;

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
	{
		signal_reciever(1);
		disable_echo_control_chars();
		av = (void *)av;
		if (ac >= 2)
			return (ft_putendl_fd("Too much argument.", 2), 1);
		if (!initialize(&shell, env))
			return (perror("Initialize"), 1);
		shell_keeper(&shell);
		start_shell(&shell);
	}
	else
		perror("ft_sh:");
	return (shell.exit_status);
}
