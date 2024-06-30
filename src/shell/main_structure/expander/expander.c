/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 21:04:48 by ysarac            #+#    #+#             */
/*   Updated: 2024/06/29 17:05:23 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

static int	dollar_expend(t_main *shell, t_tokens *token, t_env *env)
{
	size_t	i;
	size_t	start;
	char	*tmp;

	i = 0;
	tmp = ft_strdup("");
	while (token->value[i])
	{
		if (token->value[i] == '$' && !shell->in_s)
			tmp = handle_dollar_sign(tmp, token->value, &i, shell);
		else
		{
			start = i;
			while (token->value[i] && !(token->value[i] == '$' && !shell->in_s))
			{
				i++;
				if (token->value[i] == '\'' && !shell->in_d)
					shell->in_s = !shell->in_s;
				if (token->value[i] == '"' && !shell->in_s)
					shell->in_d = !shell->in_d;
			}
			tmp = append_literal(tmp, token->value, &start, &i);
		}
		if (!tmp)
			return (perror("Dollar Expend"), 0);
	}
	return (free(token->value), token->value = tmp, 1);
}

static int	home_expend(t_main *shell, t_tokens *token, t_env *env)
{
	char	*tmp;
	size_t	i;

	i = 0;
	tmp = ft_strdup("");
	while (token->value[i] && tmp)
	{
		if(token->value[i] == '~' && !shell->in_s && !shell->in_d)
		{
			if ((i > 0 && !is_whitespace(token->value[i - 1])) || (!is_whitespace(token->value[i + 1]) && token->value[i + 1] != '\0' && token->value[i + 1] != '/'))
				tmp = ft_strappend(tmp, "~", 1);
			else
				tmp = ft_strappend(tmp, find_env(env,"HOME")->value, ft_strlen(find_env(env,"HOME")->value));
		}
		else
			tmp = ft_strappend(tmp, &token->value[i], 1);
		if (token->value[i] == '\'' && !shell->in_d)
			shell->in_s = !shell->in_s;
		if (token->value[i] == '"' && !shell->in_s)
			shell->in_d = !shell->in_d;
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
	while (t)
	{
		shell->in_d = FALSE;
		shell->in_s = FALSE;
		if (ft_strnstr(t->value, "$", ft_strlen(t->value)))
		{
			if (!dollar_expend(shell, t, shell->envs))
				return (exit_in_lex_ex(shell), 0); // expenderıexit dene detaylıca
		}
		if (ft_strnstr(t->value, "~", ft_strlen(t->value)))
		{
			if (!home_expend(shell, t, shell->envs))
				return (exit_in_lex_ex(shell), 0);
		}
		t = t->next;
	}
	return (1);
}

/* 	t = shell->token;
	while (t)
	{
		printf("%s\n", t->value);
		t = t->next;
	} */