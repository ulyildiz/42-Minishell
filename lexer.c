/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:33:26 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/06/03 18:27:54 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"
#include "42-libft/libft.h"
#include <stdlib.h>
#include <stdio.h>

static char	**lex_split(char *ipt, size_t j, size_t len, size_t len2)
{
	char	**arr;
	size_t	i;
	size_t	wc;
	size_t	wl;

	if (!ipt)
		return (NULL);
	i = 0;
	wc = len - len2;
	arr = (char **)ft_calloc(1 + wc, sizeof(char *));
	if (!arr)
		return (free(ipt), 	write(2, "a", 1),NULL);
	while (i < wc)
	{
		wl = ft_strlen(&ipt[j]);
		arr[i] = ft_substr(&ipt[j], 0, wl);
		if (!arr[i])
			return (free(ipt), free_double(arr), NULL);
		j += wl + 1;
		i++;
	}
	free(ipt);
	return (arr);
}

static size_t	find_len(char *s)
{
	size_t	i;
	size_t	len;

	len = 0;
	i = -1;
	while (s[++i])
	{
		if (s[i] == '|' && s[i + 1] != '|')
			len += 2;
		else if (s[i] == '<' && s[i + 1] != '<')
			len += 2;
		else if (s[i] == '>' && s[i + 1] != '>')
			len += 2;
		else if (s[i] == '\"' || s[i] == '\'')
			len += 2;
		len++;
	}
	return (len);
}

static char	*handover_spaces(char *str, size_t *len)
{
	char	*new_one;
	size_t	i;

	i = find_len(str);
	new_one = ft_calloc(i + 1, sizeof(char));
	if (!new_one)
		return (NULL);
	while (*str)
	{
		if (*str == '|')
		{
			new_one[(*len)++] = '\0';
			new_one[(*len)++] = *str++;
			new_one[(*len)++] = '\0';
			while (*str == '|')
				new_one[(*len)++] = *str++;
		}
		else if (*str == '<' || *str == '>')
		{
			new_one[(*len)++] = '\0';
			new_one[(*len)++] = *str++;
			if (*str == '<' || *str == '>')
				new_one[(*len)++] = *str++;
			new_one[(*len)++] = '\0';
		}
		else if (*str == '\"' || *str == '\'')
		{
			new_one[(*len)++] = '\0';
			new_one[(*len)++] = *str++;
			new_one[(*len)++] = '\0';

		}
		else
			new_one[(*len)++] = *str++;
	}
	return (new_one);
}

static void	tilde_expendable(t_tokens *token, char *cmd_line)
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
}

int	lexer(t_main *shell)
{
	char	*ar;
	char	**arr;
	size_t	len;

	len = 0;
	ar = handover_spaces(shell->cmd_line, &len);
	arr = lex_split(ar, 0, ++len, ft_strlen(shell->cmd_line));
	if (!arr)
		return (perror("Lexer initialize"), 0);
	shell->token = tlist(arr);
	if (!shell->token)
		return (free_double(arr), perror("Lexer token create"), 0);
	free(arr);
	is_expendable(shell->token);
	tilde_expendable(shell->token, shell->cmd_line);
	if (!token_check(shell->token))
		return (shell->control = 0, free(shell->cmd_line), free_tokens(shell->token, 1), 1);
	t_tokens *t;
	t = shell->token;
	while (t != NULL)
	{
		printf("lexer = %s - expendable = %d - type = %d\n", t->value, t->is_expend, t->type);
		t = t->next;
	}
	return (1);
}

/* 	int i = 0;
	while (arr[i])
		printf("-%s-\n", arr[i++]); */

