/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarac <ysarac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:07:29 by ysarac            #+#    #+#             */
/*   Updated: 2024/07/01 13:07:29 by ysarac           ###   ########.fr       */
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
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}

// linuxta 1 byte leake sebep oluyor büyük 
//ihtimalle içinde null char olan envler freelenmicek

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
	while (cmd)
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

void	main_free(t_main *shell)
{
	free_env(shell->envs);
	free_tokens(shell);
	free_command(shell);
	free(shell->cmd_line);
}
