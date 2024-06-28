/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarac <ysarac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 07:29:22 by ysarac            #+#    #+#             */
/*   Updated: 2024/06/28 13:13:22 by ysarac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

void	free_double(char **arr)
{
	size_t	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->name);
		if (tmp->value && tmp->value[0] != '\0' )
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
		if (tmp->cmd_and_path)
			free(tmp->cmd_and_path);
		free(tmp);
	}
	shell->cmd = NULL;
}

/* void	main_free(t_main *shell)
{
	free_env(shell->envs);
	free_tokens(shell->token, 0);
	free_command(shell->cmd);
	free_double(shell->paths);
	free(shell->prompt);
	free(shell->cmd_line);
} */
