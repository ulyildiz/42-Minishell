/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarac <ysarac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:18:56 by ysarac            #+#    #+#             */
/*   Updated: 2024/07/01 13:18:56 by ysarac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"
#include <errno.h>
#include <readline/readline.h>
#include <stdio.h>

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
	exit(EXIT_SUCCESS);
}
	// değişken olabilir
