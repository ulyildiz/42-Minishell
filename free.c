/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:33:46 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/06/24 19:40:11 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "defines.h"
#include <unistd.h>

void	free_double(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	free_env(t_env *env)
{
	t_env *tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
}

void	free_tokens(t_main *shell)
{
	t_tokens	*t;
	t_tokens	*tmp;

	t = shell->token;
	while (t)
	{
		tmp = t;
		t = t->next;
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
	shell->token = NULL;
}

void	free_command(t_main *shell)
{
	t_command	*tmp;
	t_command	*cmd;

	cmd = shell->cmd;
	while(cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		if (tmp->value)
			free_double(tmp->value);
		if (tmp->rdrs)
			free_double(tmp->rdrs);
		free(tmp->cmd_and_path);
		free(tmp);
	}
	shell->cmd = NULL;
}

void	main_free(t_main *shell)
{
	free_env(shell->envs);
	free_tokens(shell);
	free_command(shell);
	free_double(shell->paths);
	free(shell->cmd_line);
}
