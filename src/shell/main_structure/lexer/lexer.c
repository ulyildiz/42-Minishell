/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:33:26 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/06/29 08:22:34 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"


static int	last_things(t_main *shell)
{
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
		{
			shell->in_d = !shell->in_d;
			tmp[(*j)++] = shell->cmd_line[i];
		}
		else if (shell->cmd_line[i] == '\'' && !shell->in_d)
		{
			shell->in_s = !shell->in_s;
			tmp[(*j)++] = shell->cmd_line[i];
		}
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
	return (free(tmp), last_things(shell));
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