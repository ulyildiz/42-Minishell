/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 20:18:49 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/07/22 17:37:05 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

static size_t	w_c(char **value, size_t i, size_t j, size_t len)
{
	t_bool	in_q[2];

	while (value[++i])
	{
		j = 0;
		in_q[0] = FALSE;
		in_q[1] = FALSE;
		while (value[i][j])
		{
			while (value[i][j] && is_whitespace(value[i][j]))
				j++;
			if (value[i][j])
			{
				len++;
				while (value[i][j] && (!is_whitespace(value[i][j]) || in_q[0]
						|| in_q[1]))
					toggle_quote(value[i][j++], &in_q[0], &in_q[1]);
			}
		}
		if (j == 0 && value[i][j] == '\0')
			len++;
	}
	return (len);
}

int	home_expend(t_main *shell, char **cmd, char *tmp, size_t i)
{
	tmp = ft_strdup("");
	while ((*cmd)[i] && tmp)
	{
		if ((*cmd)[i] == '~' && !shell->in_s && !shell->in_d)
		{
			if ((i > 0 && !is_whitespace((*cmd)[i - 1]))
				|| (!is_whitespace((*cmd)[i + 1]) && (*cmd)[i + 1] != '\0'
					&& (*cmd)[i + 1] != '/'))
				tmp = ft_strappend(tmp, "~", 1);
			else
			{
				if (!find_env(shell->envs, "HOME"))
					return (1);
				tmp = ft_strappend(tmp, find_env(shell->envs, "HOME")->value,
						ft_strlen(find_env(shell->envs, "HOME")->value));
			}
		}
		else
			tmp = ft_strappend(tmp, &(*cmd)[i], 1);
		toggle_quote((*cmd)[i], &shell->in_s, &shell->in_d);
		i++;
	}
	if (!tmp)
		return (perror("Home expand"), 0);
	return (free(*cmd), *cmd = tmp, 1);
}

static int	fill_tmp(char *value, size_t i, char **tmp, size_t *idx)
{
	while (value[i])
	{
		while (value[i] && is_whitespace(value[i]))
			i++;
		if (value[i])
		{
			tmp[*idx] = createword(value, &i);
			if (!tmp[(*idx)++])
				return (0);
		}
	}
	return (1);
}

char	**recreate_cmdval(t_command *cmd, size_t i, size_t j, size_t idx)
{
	char	**tmp;

	tmp = ft_calloc(w_c(cmd->value, -1, 0, 0) + 1, sizeof(char *));
	if (!tmp)
		return (NULL);
	while (cmd->value[j + 1] && !cmd->value[j][0])
		j++;
	while (cmd->value[j])
	{
		i = 0;
		if (cmd->value[j][i] == '\0')
		{
			tmp[idx] = ft_calloc(1, sizeof(char));
			if (!tmp[idx++])
				return (free_double(tmp), NULL);
			j++;
			continue ;
		}
		if (!fill_tmp(cmd->value[j], i, tmp, &idx))
			return (free_double(tmp), NULL);
		j++;
	}
	return (free_double(cmd->value), tmp);
}
