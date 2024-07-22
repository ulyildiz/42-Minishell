/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:33:34 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/07/22 16:22:09 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

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
	cmd->pid = -1;
	cmd->here_fd = -1;
	cmd->rdrs = NULL;
	cmd->next = NULL;
	cmd->prev = NULL;
	cmd->in_work = 1;
	return (cmd);
}

static int	handle_token(t_command **cmds, t_tokens **t, size_t *i)
{
	if (!rdr_position(*cmds))
		return (0);
	*i = 0;
	(*cmds)->next = cmd_struct_create(*t);
	if (!(*cmds)->next)
		return (0);
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
			cleaned_substr = ft_substr((*t)->value, start, j - start);
			if (!cleaned_substr)
				return (0);
			(*cmds)->value[(*i)++] = cleaned_substr;
		}
	}
	return (1);
}

void	parser(t_main *shell, t_tokens *t, size_t i, t_command *cmds)
{
	if (shell->control == 0)
		return ;
	cmds = cmd_struct_create(t);
	if (!cmds)
		return (shell->es = 12, exit_in_parser(shell, 0));
	shell->cmd = cmds;
	while (t)
	{
		if (!is_token(t))
		{
			if (!handle_command(&cmds, &t, &i))
				return (shell->es = 12, exit_in_parser(shell, 0));
		}
		else
		{
			if (!handle_token(&cmds, &t, &i))
				return (shell->es = 12, exit_in_parser(shell, 0));
		}
		t = t->next;
	}
	if (!rdr_position(cmds))
		return (shell->es = 12, exit_in_parser(shell, 0));
	if (!heredocs(shell, shell->cmd))
		return (shell->control = 0, exit_in_parser(shell, 2));
	return (cmds->next = NULL, free_tokens(shell));
}
