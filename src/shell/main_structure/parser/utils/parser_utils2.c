/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarac <ysarac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 19:20:48 by ysarac            #+#    #+#             */
/*   Updated: 2024/07/01 19:22:40 by ysarac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

static void	fill_rdrs(t_command *cmds, char **tmp, size_t *f)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (cmds->value[i])
	{
		if (is_rdr(cmds->value[i]) == 1)
		{
			cmds->rdrs[j++] = cmds->value[i++];
			cmds->rdrs[j++] = cmds->value[i];
		}
		else
			tmp[(*f)++] = cmds->value[i];
		i++;
	}
}

int	rdr_position(t_command *cmds)
{
	char	**tmp;
	size_t	i;
	size_t	j;
	size_t	f;

	i = 0;
	j = 0;
	f = 0;
	if (rdr_count(cmds->value) <= 0)
		return (0);
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

char	*remove_quotes(const char *str, t_bool in_s, t_bool in_d)
{
	char	*result;
	size_t	i;
	size_t	j;

	if (!str)
		return (NULL);
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
	return (result);
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

char	*extract_cleaned_substr(const char *value, size_t start, size_t end)
{
	char	*substr;
	char	*cleaned_substr;

	substr = ft_substr(value, start, end - start);
	cleaned_substr = remove_quotes(substr, FALSE, FALSE);
	free(substr);
	return (cleaned_substr);
}
