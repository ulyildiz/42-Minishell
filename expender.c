/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expender.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 21:04:48 by ysarac            #+#    #+#             */
/*   Updated: 2024/05/21 16:30:46 by ulyildiz         ###   ########.fr       */
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

static int	homedir_expend(t_tokens *token, t_env *env)
{
	t_env	*expnd_value;
	char	*tmp;

	if (token->is_expend != NONE)
		return (1);
	expnd_value = find_env(env, "HOME");
	if (!expnd_value)
		return (0);
	tmp = token->value;
	token->value = ft_strjoin(expnd_value->value, token->value + 1);
	free(tmp);
	if (!token->value)
		return (perror("Homedir expand"), 0);
	return (1);
}

static int	home_expend(t_tokens *token, t_env *env)
{
	t_env	*expnd_value;

	if (token->is_expend != NONE)
		return (1);
	expnd_value = find_env(env, "HOME");
	if (!expnd_value)
		return (0);
	free(token->value);
	token->value = ft_strdup(expnd_value->value);
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
	while (t != NULL)
	{
		if (ft_strnstr(t->value, "$", ft_strlen(t->value)))
		{
			if (!dollar_expend(t, shell->envs))
				return (0);
		}
		else if (ft_strnstr(t->value, "~/", ft_strlen(t->value)))
		{
			if (!homedir_expend(t, shell->envs))
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
/* 	while (t != NULL)
	{
		printf("lexer = %s - quote = %d - type = %d\n", t->value, t->is_expend, t->type);
		t = t->next;
	} */

// "" içinde olanlarda sadece $ değişkenleri expendlencek
// '' içinde olanlarda hiçbir değişken expendlenmeyecek
// ~ ve ~/ işaretleri expendlencek mi? expend sırasında sağı ve solu whitespace olmalı
