/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 20:18:49 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/07/13 20:25:33 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functions.h>

static size_t	w_c(char **value)
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

static char	*createword(t_command *cmd, size_t idx, size_t j, size_t *i)
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

char	**recreate_cmdval(t_command *cmd)
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
					return (free_double(tmp), NULL);
			}
		}
		j++;
	}
	return (free_double(cmd->value), tmp);
}
