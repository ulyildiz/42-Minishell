/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 20:18:49 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/07/19 18:48:29 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"
#include "libft.h"
#include <stdio.h>

static size_t	w_c(char **value, size_t i, size_t j, size_t len)
{
	t_bool in_q[2];

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
				while (value[i][j] && (!is_whitespace(value[i][j]) || in_q[0] || in_q[1]))
				{
					toggle_quote(value[i][j], &in_q[0], &in_q[1]);
					j++;
				}
			}
		}
		if (j == 0 && value[i][j] == '\0')
			len++;
	}
	return (len);
}

char	**recreate_cmdval(t_command *cmd)
{
	size_t	j;
	char	**tmp;
	size_t	idx;
	size_t	i;

	idx = 0;
	j = 0;
	tmp = ft_calloc(w_c(cmd->value, -1, 0, 0) + 1, sizeof(char *));
	if (!tmp)
		return (NULL);
	while (cmd->value[j])
	{
		i = 0;
		if (cmd->value[j][i] == '\0')
		{
			tmp[idx] = ft_calloc(1, sizeof(char));
			if (!tmp[idx++])
				return (free_double(tmp), NULL);
			j++;
			continue;
		}
		while (cmd->value[j][i])
		{
			while (cmd->value[j][i] && is_whitespace(cmd->value[j][i]))
				i++;
			if (cmd->value[j][i])
			{
				tmp[idx] = createword(cmd, j, &i);
				if (!tmp[idx++])
					return (free_double(tmp), NULL);
			}
		}
		j++;
	}
	return (free_double(cmd->value), tmp);
}
