/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 08:28:02 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/06/29 08:37:07 by ulyildiz         ###   ########.fr       */
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
	strerror(ENOMEM);
	exit(ENOMEM);
}
