/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 19:20:48 by ysarac            #+#    #+#             */
/*   Updated: 2024/07/22 16:44:41 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"
#include "libft.h"
#include <stdlib.h>

static void	fill_rdrs(t_command *cmds, char **tmp, size_t *f)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (cmds->value[i])
	{
		if (is_rdr(cmds->value[i]))
		{
			cmds->rdrs[j++] = cmds->value[i++];
			cmds->rdrs[j++] = cmds->value[i];
		}
		else
			tmp[(*f)++] = cmds->value[i];
		i++;
	}
	tmp[*f] = NULL;
}

int	rdr_position(t_command *cmds)
{
	char	**tmp;
	size_t	i;
	size_t	f;

	i = 0;
	f = 0;
	if (rdr_count(cmds->value) <= 0)
		return (1);
	while (cmds->value[i])
		i++;
	tmp = ft_calloc(i - rdr_count(cmds->value) + 1, sizeof(char *));
	if (!tmp)
		return (0);
	cmds->rdrs = ft_calloc((rdr_count(cmds->value) + 1), sizeof(char *));
	if (!cmds->rdrs)
		return (free_double(tmp), 0);
	fill_rdrs(cmds, tmp, &f);
	free(cmds->value);
	cmds->value = tmp;
	return (1);
}

char	*create_word(t_command *cmd, size_t j, size_t *i)
{
	size_t	start;
	t_bool	in_s;
	t_bool	in_d;
	size_t	len;

	start = *i;
	in_s = FALSE;
	in_d = FALSE;
	while (cmd->value[j][*i] && (!is_whitespace(cmd->value[j][*i]) || in_s
			|| in_d))
	{
		toggle_quote(cmd->value[j][*i], &in_s, &in_d);
		if ((cmd->value[j][*i] == '\'' && !in_d) || (cmd->value[j][*i] == '"'
				&& !in_s))
		{
			(*i)++;
			continue ;
		}
	}
	len = (*i) - start;
	return (ft_substr(cmd->value[j], start, len));
}

size_t	find_word_end(const char *value, size_t start, t_bool *in_d,
		t_bool *in_s)
{
	size_t	j;

	j = start;
	while (value[j])
	{
		toggle_quote(value[j], in_s, in_d);
		if (is_whitespace(value[j]) && !(*in_d) && !(*in_s))
			break ;
		j++;
	}
	return (j);
}
