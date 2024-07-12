/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 21:05:33 by ysarac            #+#    #+#             */
/*   Updated: 2024/07/12 12:13:18 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

static char	*expand_dollar_question(char *tmp, t_main *shell)
{
	char	*code;

	code = ft_itoa(shell->exit_status);
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
	while (ft_isalpha(token_value[*i + j]) || token_value[*i + j] == '_')
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
	else if (ft_isalpha(token_value[*i + 1]) || token_value[*i + 1] == '_')
		tmp = expand_variable(tmp, token_value, i, shell->envs);
	else
	{
		tmp = ft_strappend(tmp, "$", 1);
		(*i)++;
	}
	return (tmp);
}

size_t	w_c(char **value)
{
	size_t i, j, len;
	t_bool in_s, in_d;

	i = 0;
	len = 0;
	while (value[i])
	{
		j = 0;
		in_s = FALSE;
		in_d = FALSE;
		while (value[i][j])
		{
			while (value[i][j] && is_whitespace(value[i][j]))
				j++;
			if (value[i][j])
			{
				len++;
				while (value[i][j] && (!is_whitespace(value[i][j]) || in_s || in_d))
				{
					toggle_quote(value[i][j], &in_s, &in_d);
					j++;
				}
			}
		}
		i++;
	}
	return (len);
}

char	*createword(t_command *cmd, size_t idx, size_t j, size_t *i)
{
	size_t	start;
	t_bool	in_s;
	t_bool	in_d;
	size_t	len;
	char 	*tmp;

	start = *i;
	in_s = FALSE;
	in_d = FALSE;
	while (cmd->value[j][*i] && (!is_whitespace(cmd->value[j][*i]) || in_s || in_d))
	{
		toggle_quote(cmd->value[j][*i], &in_s, &in_d);
		if ((cmd->value[j][*i] == '\'' && !in_d) || (cmd->value[j][*i] == '"' && !in_s))
		{
			(*i)++;
			continue ;
		}
		(*i)++;
	}
	len = (*i) - start;
	tmp = ft_calloc(len + 1, sizeof(char));
	if (!tmp)
		return (NULL);
	in_s = FALSE;
	in_d = FALSE;
	size_t	k = start;
	size_t	tmp_idx = 0;
	while (cmd->value[j][k] && k < *i /* && (!is_whitespace(cmd->value[j][*i]) || in_s || in_d) */)
	{
		toggle_quote(cmd->value[j][k], &in_s, &in_d);
		if ((cmd->value[j][k] == '\'' && !in_d) || (cmd->value[j][k] == '"' && !in_s))
		{
			(k)++;
			continue ;
		}
		tmp[tmp_idx++] = cmd->value[j][k]; 	
		(k)++;
	}
	return (tmp);
}


char **recreate_cmdval(t_command *cmd)
{
	size_t	j;
	char	**tmp;
	size_t	idx;
	size_t	i;

	idx = 0;
	j = 0;
	tmp = ft_calloc(w_c(cmd->value) + 1, sizeof(char *));
	if (!tmp)
		return (NULL);
	while (cmd->value[j])
	{
		i = 0;
		while (cmd->value[j][i])
		{
			while (cmd->value[j][i] && is_whitespace(cmd->value[j][i]))
				i++;
			if (cmd->value[j][i])
			{
				tmp[idx] = createword(cmd, idx, j, &i);
				if (!tmp[idx++])
					return (NULL);
			}
		}
		j++;
	}
	return (free_double(cmd->value), tmp);
}
