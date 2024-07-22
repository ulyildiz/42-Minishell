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
#include <stdio.h>

t_env	*find_env(t_env *envs, char *wanted)
{
	if (!wanted)
		return (NULL);
	while (envs)
	{
		if (!ft_strncmp(envs->name, wanted, ft_strlen(wanted)) && \
		!ft_strncmp(envs->name, wanted, ft_strlen(envs->name)))
			return (envs);
		envs = envs->next;
	}
	return (NULL);
}

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

	av = (void *)av;
	signal_reciever(1);
	disable_echo_control_chars();
	if (ac >= 2)
		return (ft_putendl_fd("Too much argument.", 2), 1);
	if (!initialize(&shell, env))
		return (perror("Initialize"), 1);
	shell_keeper(&shell);
	start_shell(&shell);
	return (shell.es);
}
