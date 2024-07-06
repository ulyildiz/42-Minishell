/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:33:26 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/07/06 11:56:07 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

void	remove_unnecessary_space(t_main *shell)
{
	t_tokens	*tmp;
	t_tokens	*prev;
	t_tokens	*first;

	tmp = shell->token;
	first = tmp;
	while (tmp)
	{
		if (!is_space(tmp->value))
		{
			if (first == tmp)
				shell->token = tmp->next;
			else
				prev->next = tmp->next;
			free(tmp->value);
			free(tmp);
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

static void	last_things(t_main *shell)
{
	remove_unnecessary_space(shell); // dene
	if (!token_check(shell))
	{
		shell->control = 0;
		shell->exit_status = 258;
		free_tokens(shell);
		free(shell->cmd_line);
	}
}

static void	looping(t_main *shell, size_t input_len, size_t *j)
{
	size_t	i;

	i = 0;
	while (i < input_len)
	{
		if (shell->cmd_line[i] == '|' && !shell->in_s && !shell->in_d)
			listing_token(shell, shell->tmp, j, "|");
		else if (shell->cmd_line[i] == '<' && !shell->in_s && !shell->in_d)
			listing_rdr(shell, j, &i, "<");
		else if (shell->cmd_line[i] == '>' && !shell->in_s && !shell->in_d)
			listing_rdr(shell, j, &i, ">");
		else if (shell->cmd_line[i] == '"' && !shell->in_s)
		{
			shell->in_d = !shell->in_d;
			shell->tmp[(*j)++] = shell->cmd_line[i];
		}
		else if (shell->cmd_line[i] == '\'' && !shell->in_d)
		{
			shell->in_s = !shell->in_s;
			shell->tmp[(*j)++] = shell->cmd_line[i];
		}
		else
			shell->tmp[(*j)++] = shell->cmd_line[i];
		i++;
	}
}

void	lexer(t_main *shell)
{
	size_t	input_len;
	size_t	j;

	j = 0;
	input_len = ft_strlen(shell->cmd_line);
	shell->tmp = (char *)malloc((input_len + 1) * sizeof(char));
	if (!shell->tmp)
		return (exit_in_lex_ex(shell));
	shell->in_s = FALSE;
	shell->in_d = FALSE;
	shell->token = NULL;
	looping(shell, input_len, &j);
	if (j > 0)
	{
		shell->tmp[j] = '\0';
		if (!tlist(&shell->token, shell->tmp))
			return (free(shell->tmp), exit_in_lex_ex(shell));
	}
	return (free(shell->tmp), last_things(shell));
}

/* 	t_tokens *t;
	t = shell->token;
	printf("a = %p\n", t);
	while (t != NULL)
	{
		printf("lexer = %s/%zu - expendable = %d - type = %d\n", t->value,
				ft_strlen(t->value), t->is_expend, t->type);
		t = t->next;
	} */
/* 	int i = 0;
	while (arr[i])
		printf("-%s-\n", arr[i++]); */