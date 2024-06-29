/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 08:28:02 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/06/29 10:15:45 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"
#include <errno.h>

void	exit_in_lexer(t_main *shell)
{
	free_env(shell->envs);
	free_double(shell->env_for_execve_function);
	free_tokens(shell);
	free(shell->cmd_line);
	ft_putend_fd(strerror(ENOMEM), 2);
	exit(ENOMEM);
}

void	exit_in_expender(t_main *shell)
{
	free_env(shell->envs);
	free_double(shell->env_for_execve_function);
	free_tokens(shell);
	free(shell->cmd_line);
	ft_putend_fd(strerror(ENOMEM), 2);
	exit(ENOMEM);
}
