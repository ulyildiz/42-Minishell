/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarac <ysarac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 07:29:22 by ysarac            #+#    #+#             */
/*   Updated: 2024/06/14 07:32:47 by ysarac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "functions.h"

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

void	free_tokens(t_tokens *tokens, int flag)
{
	t_tokens	*tmp;

	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		if (flag == 1 && tmp->value)
			free(tmp->value);
		free(tmp);
	}
}

void	free_command(t_command *cmd)
{
	t_command	*tmp;

	while(cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		if (tmp->value)
			free_double(tmp->value);
		free(tmp->cmd_and_path);
/* 		free(tmp->cmd_and_path); */
		free(tmp);
	}
}

void	main_free(t_main *shell)
{
	free_env(shell->envs);
	free_tokens(shell->token, 0);
	free_command(shell->cmd);
	free_double(shell->paths);
	free(shell->prompt);
	free(shell->cmd_line);
}