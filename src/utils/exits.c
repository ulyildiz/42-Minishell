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
#include "libft.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

void	exit_in_lex_ex(t_main *shell)
{
	free_env(shell->envs);
	free_double(shell->env_for_execve_function);
	free_tokens(shell);
	rl_clear_history();
	free(shell->cmd_line);
	exit(shell->exit_status);
}

void	exit_in_parser(t_main *shell)
{
	perror("Parser");
	free_env(shell->envs);
	free_double(shell->env_for_execve_function);
	free_tokens(shell);
	free_command(shell, NULL);
	rl_clear_history();
	free(shell->cmd_line);
	exit(shell->exit_status);
}

void	exit_in_exec(t_main *shell)
{
	perror("Executer");
	free_env(shell->envs);
	free_double(shell->env_for_execve_function);
	free_double(shell->paths);
	free_command(shell, NULL);
	rl_clear_history();
	free(shell->cmd_line);
	exit(shell->exit_status);
}

void	exit_for_fork(t_main *shell)
{
	free_command(shell, NULL);
	free_env(shell->envs);
	free_double(shell->paths);
	free_double(shell->env_for_execve_function);
	free(shell->cmd_line);
	rl_clear_history();
	exit(shell->exit_status);
}
