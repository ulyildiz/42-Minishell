/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 08:28:02 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/06/29 17:37:48 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"
#include <errno.h>
#include <stdio.h>
#include <readline/readline.h>

void	exit_in_lex_ex(t_main *shell)
{
	free_env(shell->envs);
	free_double(shell->env_for_execve_function);
	free_tokens(shell);
	free(shell->cmd_line);
	exit(ENOMEM);
}

void	exit_in_parser(t_main *shell)
{
	free_env(shell->envs);
	free_double(shell->env_for_execve_function);
	free_tokens(shell);
	free_command(shell);
	free(shell->cmd_line);
	exit(ENOMEM);
}

void	main_exit(t_main *shell)
{
	free_env(shell->envs);
	free_double(shell->env_for_execve_function);
	if (shell->token)
		free_tokens(shell);
	if (shell->cmd)
		free_command(shell);
	free(shell->cmd_line);
	exit(ENOMEM);
}

void	exit_for_fork(t_main *shell)
{
	free_command(shell);
	free_tokens(shell);
	free_env(shell->envs);
	free_double(shell->paths);
	free_double(shell->env_for_execve_function);
	free(shell->cmd_line);
	clear_history();
	exit(EXIT_SUCCESS); // değişken olabilir
}