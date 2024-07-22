/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 21:05:33 by ysarac            #+#    #+#             */
/*   Updated: 2024/07/22 16:52:05 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"
#include "libft.h"
#include <stdlib.h>

static char	*expand_dollar_question(char *tmp, t_main *shell)
{
	char	*code;

	code = ft_itoa(shell->es);
	if (!code)
	{
		if (tmp)
			free(tmp);
		return (NULL);
	}
	tmp = ft_strappend(tmp, code, ft_strlen(code));
	free(code);
	return (tmp);
}

static char	*expand_variable(char *tmp, const char *token_value, size_t *i,
		t_env *env)
{
	size_t	j;
	char	*new_tmp;
	t_env	*expnd_value;

	j = 0;
	(*i)++;
	if (ft_isdigit(token_value[*i]) || \
	token_value[*i + 1] == '"' || token_value[*i + 1] == '\'')
		return ((*i)++, tmp);
	while ((ft_isalnum(token_value[*i + j]) || token_value[*i + j] == '_'))
		j++;
	new_tmp = ft_strndup(&token_value[*i], j);
	if (!new_tmp)
	{
		free(tmp);
		return (NULL);
	}
	expnd_value = find_env(env, new_tmp);
	if (expnd_value)
		tmp = ft_strappend(tmp, expnd_value->value,
				ft_strlen(expnd_value->value));
	free(new_tmp);
	*i += j;
	return (tmp);
}

char	*append_literal(char *tmp, char *token_value, size_t *start, size_t *i)
{
	tmp = ft_strappend(tmp, &token_value[*start], *i - *start);
	return (tmp);
}

char	*handle_dollar_sign(char *tmp, const char *token_value, size_t *i,
		t_main *shell)
{
	if (token_value[*i + 1] == '?')
	{
		tmp = expand_dollar_question(tmp, shell);
		*i += 2;
	}
	else if (token_value[*i + 1] == '\0')
	{
		tmp = ft_strappend(tmp, "$", 1);
		(*i)++;
	}
	else if (ft_isalnum(token_value[*i + 1]) || token_value[*i + 1] == '_' \
	|| ((token_value[*i + 1] == '"' || token_value[*i + 1] == '\'') \
	&& !shell->in_s && !shell->in_d))
		tmp = expand_variable(tmp, token_value, i, shell->envs);
	else
	{
		tmp = ft_strappend(tmp, "$", 1);
		(*i)++;
	}
	return (tmp);
}

char	*remove_quotes(char *str, t_bool in_s, t_bool in_d)
{
	char	*result;
	size_t	i;
	size_t	j;

	result = allocate_result(str);
	if (!result)
		return (NULL);
	j = 0;
	i = 0;
	while (str[i])
	{
		toggle_quote(str[i], &in_s, &in_d);
		if ((str[i] == '\'' && !in_d) || (str[i] == '"' && !in_s))
		{
			i++;
			continue ;
		}
		result[j++] = str[i++];
	}
	result[j] = '\0';
	return (free(str), result);
}
