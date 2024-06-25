/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expender.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 21:04:48 by ysarac            #+#    #+#             */
/*   Updated: 2024/06/25 20:30:40 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42-libft/libft.h"
#include "functions.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static int	dollar_expend(t_tokens *token, t_env *env)
{
	size_t	i;
	size_t	start;
	char	*tmp;

	if (token->is_expend == WITHIN_Q)
		return (1);
	i = 0;
	tmp = ft_strdup("");
	while (token->value[i])
	{
		if (token->value[i] == '$')
			tmp = handle_dollar_sign(tmp, token->value, &i, env);
		else
		{
			start = i;
			while (token->value[i] && token->value[i] != '$')
				i++;
			tmp = append_literal(tmp, token->value, &start, &i);
		}
		if (!tmp)
			return (perror("Dollar Expend"), 0);
	}
	free(token->value);
	token->value = tmp;
	return (1);
}

static int	home_expend(t_tokens *token, t_env *env)
{
	char	*tmp;
	size_t	i;

	if (token->is_expend == WITHIN_D_Q || token->is_expend == WITHIN_Q)
		return (1);
	i = 0;
	tmp = ft_strdup("");
	while (token->value[i] && tmp)
	{
		if(token->value[i] == '~')
		{
			if ((i > 0 && !is_whitespace(token->value[i - 1])) || (!is_whitespace(token->value[i + 1]) && token->value[i + 1] != '\0' && token->value[i + 1] != '/'))
				tmp = ft_strappend(tmp, "~", 1);
			else
				tmp = ft_strappend(tmp, find_env(env,"HOME")->value, ft_strlen(find_env(env,"HOME")->value));
		}
		else
			tmp = ft_strappend(tmp, &token->value[i], 1);
		i++;
	}
	token->value = tmp;
	if (!token->value)
		return (perror("Home expand"), 0);
	return (1);
}

int	expender(t_main *shell)
{
	t_tokens	*t;

	if (shell->control == 0)
		return (1);
	t = shell->token;
	shell->in_d = FALSE;
	shell->in_s = FALSE;
	while (t)
	{
		if (ft_strnstr(t->value, "$", ft_strlen(t->value)))
		{
			if (!dollar_expend(t, shell->envs))
				return (0);
		}
		else if (ft_strnstr(t->value, "~", ft_strlen(t->value)))
		{
			if (!home_expend(t, shell->envs))
				return (0);
		}
		t = t->next;
	}
	return (remove_quotes(&shell->token), 1);
}

/* 	t = shell->token;
	while (t)
	{
		printf("%s\n", t->value);
		t = t->next;
	} */