/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 21:05:33 by ysarac            #+#    #+#             */
/*   Updated: 2024/06/29 11:29:00 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "functions.h"

static char	*expand_dollar_dollar(char *tmp)
{
	char	*pid_str;
	char	*new_tmp;

	pid_str = ft_itoa(getpid());
	if (!pid_str)
		return (NULL);
	new_tmp = ft_strappend(tmp, pid_str, ft_strlen(pid_str));
	free(pid_str);
	return (new_tmp);
}

static char	*expand_dollar_question(char *tmp)
{
	return (ft_strappend(tmp, "0", 1));
}

static char	*expand_variable(char *tmp, const char *token_value, size_t *i,
		t_env *env)
{
	size_t	j;
	char	*new_tmp;
	t_env	*expnd_value;

	j = 0;
	(*i)++;
	while (ft_isalpha(token_value[*i + j])) // $A3 gibi durumda ne yapıcak
	{
		j++;
	}
	new_tmp = ft_strndup(&token_value[*i], j);
	expnd_value = find_env(env, new_tmp);
	if (expnd_value)
	{
		tmp = ft_strappend(tmp, expnd_value->value,
				ft_strlen(expnd_value->value));
	}
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
		t_env *env)
{
	if (token_value[*i + 1] == '$')
	{
		tmp = expand_dollar_dollar(tmp);
		*i += 2;
	}
	else if (token_value[*i + 1] == '?')
	{
		tmp = expand_dollar_question(tmp);
		*i += 2;
	}
	else if (token_value[*i + 1] == '\0')
	{
		tmp = ft_strappend(tmp, "$", 1);
		(*i)++;
	}
	else if (ft_isalpha(token_value[*i + 1]))
	{
		tmp = expand_variable(tmp, token_value, i, env);
	}
/* 	else
	{
		tmp = ft_strappend(tmp, "$", 1); //bak
		(*i)++;
	} */
	return (tmp);
}
