/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarac <ysarac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:33:26 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/06/14 11:12:05 by ysarac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"


static int	last_things(t_main *shell)
{
	is_expendable(shell->token);
	if (!token_check(shell))
		return (shell->control = 0, 1);
	return (1);
}

static void	looping(t_main *shell, char *tmp, size_t input_len, size_t *j)
{
	size_t	i;

	i = 0;
	while (i < input_len)
	{
		if (shell->cmd_line[i] == '|' && !shell->in_s && !shell->in_d)
			listing_token(shell, tmp, j, "|");
		else if (shell->cmd_line[i] == '<' && !shell->in_s && !shell->in_d)
			listing_rdr(shell, tmp, j, &i, "<");
		else if (shell->cmd_line[i] == '>' && !shell->in_s && !shell->in_d)
			listing_rdr(shell, tmp, j, &i, ">");
		else if (shell->cmd_line[i] == '"' && !shell->in_s)
			listing_dquote(shell, tmp, j, "\"");
		else if (shell->cmd_line[i] == '\'' && !shell->in_d)
			listing_squote(shell, tmp, j, "'");
		else
			tmp[(*j)++] = shell->cmd_line[i];
		i++;
	}
}

int	lexer(t_main *shell)
{
	char	*tmp;
	size_t	input_len;
	size_t	j;

	j = 0;
	input_len = ft_strlen(shell->cmd_line);
	tmp = (char *)malloc((input_len + 1) * sizeof(char));
	if (!tmp)
		return (0);
	shell->in_s = FALSE;
	shell->in_d = FALSE;
	shell->token = NULL;
	looping(shell, tmp, input_len, &j);
	if (j > 0)
	{
		tmp[j] = '\0';
		tlist(&shell->token, tmp);
	}
	return (last_things(shell));
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

/* 		else if (shell->cmd_line[i] == '<' && shell->cmd_line[i + 1] == '<'
				&& !shell->in_s && !shell->in_d)
			listing_token(shell, tmp, j, "<<");
		else if (shell->cmd_line[i] == '>' && shell->cmd_line[i + 1] == '>'
				&& !shell->in_s && !shell->in_d) 
			listing_token(shell, tmp, j, ">>"); */