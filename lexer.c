/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarac <ysarac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:33:26 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/06/07 16:00:58 by ysarac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"
#include "42-libft/libft.h"
#include <stdlib.h>
#include <stdio.h>

/* static void	tilde_expendable(t_tokens *token, char *cmd_line)
{
	size_t		i;
	t_tokens	*tmp;

	tmp = token;
	i = 0;
	while (tmp)
	{
		while (cmd_line[i] != '\0' && cmd_line[i] != '~')
			i++;
		while (tmp && !ft_strnstr(tmp->value, "~", ft_strlen(tmp->value)))
			tmp = tmp->next;
		if (i != 0 && cmd_line[i] != '\0' && is_whitespace(cmd_line[i - 1]) == 1)
			tmp->is_expend = NONE_TILDE;
		if (cmd_line[i] != '\0' && is_whitespace(cmd_line[i + 1])
			&& cmd_line[i + 1] != '\0' && cmd_line[i + 1] != '/')
			tmp->is_expend = NONE_TILDE;
		if (cmd_line[i] == '\0' || !tmp)
			break;
		i++;
		tmp = tmp->next;
	}
} */

int	lexer(t_main *shell)
{
	char	*token;
	size_t	input_len;
	t_bool	in_single;
	t_bool	in_double;
	size_t 	j;
	size_t	k;
	
	shell->token = NULL;
	input_len = ft_strlen(shell->cmd_line);
	token = (char *)malloc(input_len * sizeof(char));
	if (!token)
		return (perror("Lexer"), 0);
	in_single = false;
	in_double = false;
	k = 0;
	j = 0;
	while (k < input_len)
	{
		if(shell->cmd_line[k] == '|' && !in_single && !in_double)
		{
			if (j > 0)
			{
				token[j] = '\0';
				tlist(&shell->token, token);
				j = 0;
			}
			tlist(&shell->token, "|");
		}
		else if(shell->cmd_line[k] == '\'' && !in_double)
		{
			if (j > 0)
			{
				token[j] = '\0';
				tlist(&shell->token, token);
				j = 0;
			}
			in_single = !in_single;
			tlist(&shell->token, "\'");
		}
		else if(shell->cmd_line[k] == '"' && !in_single)
		{
			if (j > 0)
			{
				token[j] = '\0';
				tlist(&shell->token, token);
				j = 0;
			}
			in_double = !in_double;
			tlist(&shell->token, "\"");
		}
		else
			token[j++] = shell->cmd_line[k];
		k++;
	}
	if(j > 0)
	{
		token[j] = '\0';
		tlist(&shell->token, token);
	}
	free(token);
	is_expendable(shell->token);
	return (1);
}
/* 
	t_tokens *t;
	t = shell->token;
	while (t != NULL)
	{
		printf("lexer = %s/%zu - expendable = %d - type = %d\n", t->value, ft_strlen(t->value), t->is_expend, t->type);
		t = t->next;
	} */
/* 	int i = 0;
	while (arr[i])
		printf("-%s-\n", arr[i++]); */

