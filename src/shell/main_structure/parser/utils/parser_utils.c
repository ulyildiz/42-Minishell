/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarac <ysarac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:33:31 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/06/28 13:17:42 by ysarac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "libft.h"

int	is_token(t_tokens *t)
{
	if (t->type == PIPE)
		return (1);
	return (0);
}

size_t	rdr_count(char **str)
{
	size_t	len;
	size_t	i;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (!ft_strncmp(str[i], "<", 1) && ft_strlen(str[i]) == 1 && ++i)
			len++;
		else if (!ft_strncmp(str[i], ">", 1) && ft_strlen(str[i]) == 1 && ++i)
			len++;
		else if (!ft_strncmp(str[i], ">>", 2) && ft_strlen(str[i]) == 2 && ++i)
			len++;
		else if (!ft_strncmp(str[i], "<<", 2) && ft_strlen(str[i]) == 2 && ++i)
			len++;
		i++;
	}
	len *= 2;
	return (len);
}

void	toggle_quote(char c, t_bool *in_s, t_bool *in_d)
{
	if (c == '\'' && !(*in_d))
		*in_s = !(*in_s);
	else if (c == '"' && !(*in_s))
		*in_d = !(*in_d);
}

int	is_rdr(char *strs)
{
	int		i;
	t_bool	in_s;
	t_bool	in_d;

	i = 0;
	in_s = FALSE;
	in_d = FALSE;
	while (strs[i])
	{
		toggle_quote(strs[i], &in_s, &in_d);
		if (!in_s && !in_d)
		{
			if (strs[i] == '<')
				return (1);
			if (strs[i] == '>')
				return (1);
		}
		i++;
	}
	return (0);
}

char	*allocate_result(const char *str)
{
	size_t	len;
	char	*result;

	len = ft_strlen(str);
	result = (char *)ft_calloc(len + 1, sizeof(char));
	return (result);
}
