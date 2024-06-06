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

size_t	expended_len(char *old_v, char *expend_v, char *orj_expend_v)
{
	size_t	len;

	len = ft_strlen(old_v) - ft_strlen(orj_expend_v) + ft_strlen(expend_v);
	return (len);
}

char	*expend_placement(char *old_value, char *expend_value, char *orj_expend_v)
{
	char	*new_value;
	size_t	i;
	size_t	j;
	size_t	f;

	i = 0;
	j = 0;
	f = 0;
	new_value = ft_calloc(1 + expended_len(old_value, expend_value, orj_expend_v), sizeof(char));
	if (!new_value)
		return (0);
	while(old_value[f] && !ft_strnstr(&old_value[f], orj_expend_v, ft_strlen(orj_expend_v)))
		new_value[i++] = old_value[f++];
	while (expend_value[j])
		new_value[i++] = expend_value[j++];
	f += ft_strlen(orj_expend_v);
	while(old_value[f])
		new_value[i++] = old_value[f++];
	free(old_value);
	return (new_value);
}
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
	tmp = ft_strjoin(expnd_value->value, "/");
	if (!tmp)
		return (perror("Homedir expend"), 0);
	token->value = expend_placement(token->value, tmp, "~/");
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
	token->value = expend_placement(token->value, expnd_value->value, "~");
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
	return (/* remove_quotes(&shell->token), */ 1);
}
