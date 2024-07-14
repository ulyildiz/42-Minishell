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

#include "defines.h"
#include <stdlib.h>
#include <unistd.h>

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
		if (tmp->name)
			free(tmp->name);
		if (tmp->value)
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

void	free_command(t_main *shell, t_command *tp)
{
	t_command	*tmp;
	t_command	*cmd;

	if (!tp)
		cmd = shell->cmd;
	else
		cmd = tp;
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
	if (!tp)
		shell->cmd = NULL;
}

void	free_c(t_command *c)
{
	if (c->cmd_and_path)
		free(c->cmd_and_path);
	if (c->value)
		free_double(c->value);
	if (c->rdrs)
		free_double(c->rdrs);
/* 	if (c->fd[0] != STDIN_FILENO)
		close(c->fd[0]); */
	if (c->fd[1] != STDOUT_FILENO)
		close(c->fd[1]);
	free(c);
}
