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
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

void	exit_in_lex(t_main *shell)
{
	free_env(shell->envs);
	free_double(shell->env_for_execve_function);
	free_tokens(shell);
	rl_clear_history();
	free(shell->cmd_line);
	exit(shell->es);
}

void	exit_in_expander(t_main *shell)
{
	perror("Expander");
	free_env(shell->envs);
	free_double(shell->env_for_execve_function);
	rl_clear_history();
	free(shell->cmd_line);
	free_command(shell, NULL);
	exit(shell->es);
}

void	exit_in_parser(t_main *shell, int in_here)
{
	if (in_here == 0)
		perror("Parser");
	free_tokens(shell);
	free_command(shell, NULL);
	free(shell->cmd_line);
	if (in_here != 2)
	{
		rl_clear_history();
		free_env(shell->envs);
		free_double(shell->env_for_execve_function);
		exit(shell->es);
	}
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
	exit(shell->es);
}

void	exit_for_fork(t_main *shell)
{
	free_command(shell, NULL);
	free_env(shell->envs);
	free_double(shell->paths);
	free_double(shell->env_for_execve_function);
	free(shell->cmd_line);
	rl_clear_history();
	exit(shell->es);
}
