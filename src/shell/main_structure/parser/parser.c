/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarac <ysarac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:33:34 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/07/01 19:30:19 by ysarac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

static t_command	*cmd_struct_create(t_tokens *token)
{
	t_command	*cmd;
	size_t		i;

	if (!token)
		return (NULL);
	cmd = (t_command *)ft_calloc(1, sizeof(t_command));
	if (!cmd)
		return (NULL);
	if (is_token(token))
		token = token->next;
	i = length_to_token(token);
	cmd->value = (char **)ft_calloc((i + 1), sizeof(char *));
	if (!cmd->value)
		return (free(cmd), NULL);
	cmd->value[i] = NULL;
	cmd->where_p = NONE_P;
	cmd->fd[0] = STDIN_FILENO;
	cmd->fd[1] = STDOUT_FILENO;
	cmd->rdrs = NULL;
	cmd->cmd_and_path = NULL;
	return (cmd);
}

static int	handle_token(t_command **cmds, t_tokens **t, size_t *i)
{
	rdr_position(*cmds);
	*i = 0;
	(*cmds)->next = cmd_struct_create(*t);
	if (!(*cmds)->next)
		return (perror("Parser"), 0);
	(*cmds)->where_p = R_P;
	(*cmds)->next->prev = *cmds;
	*cmds = (*cmds)->next;
	(*cmds)->where_p = L_P;
	return (1);
}

static int	handle_command(t_command **cmds, t_tokens **t, size_t *i)
{
	t_bool	in_d;
	t_bool	in_s;
	size_t	j;
	size_t	start;
	char	*cleaned_substr;

	j = 0;
	in_s = FALSE;
	in_d = FALSE;
	while ((*t)->value[j])
	{
		while ((*t)->value[j] && \
		is_whitespace((*t)->value[j]) && !in_d && !in_s)
			j++;
		start = j;
		if ((*t)->value[j])
		{
			j = find_word_end((*t)->value, j, &in_d, &in_s);
			cleaned_substr = extract_cleaned_substr((*t)->value, start, j);
			if (!cleaned_substr)
				return (0);
			(*cmds)->value[(*i)++] = cleaned_substr;
		}
	}
	return (1);
}

int	parser(t_main *shell, t_tokens *t, size_t i)
{
	t_command	*cmds;

	if (shell->control == 0)
		return (1);
	cmds = cmd_struct_create(t);
	if (!cmds)
		return (perror("Parser"), 0);
	shell->cmd = cmds;
	while (t)
	{
		if (!is_token(t))
		{
			if (!handle_command(&cmds, &t, &i))
				return (0);
		}
		else
		{
			if (!handle_token(&cmds, &t, &i))
				return (0);
		}
		t = t->next;
	}
	rdr_position(cmds);
	cmds->next = NULL;
	return (free_tokens(shell), 1);
}

/* 	while (shell->cmd)
	{
		printf("value = %s - prev = %p - next = %p\n", shell->cmd->value[0],
				shell->cmd->prev, shell->cmd->next);
		shell->cmd = shell->cmd->next;
	} */