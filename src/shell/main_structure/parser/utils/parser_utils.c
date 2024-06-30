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

#include "functions.h"



int	is_token(t_tokens *t)
{
	if (t->type == PIPE && (t->is_expend != WITHIN_D_Q
			&& t->is_expend != WITHIN_Q))
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
		if (!ft_strncmp(str[i], "<", 1) && ft_strlen(str[i]) == 1 && i++)
			len++;
		else if (!ft_strncmp(str[i], ">", 1) && ft_strlen(str[i]) == 1 && i++)
			len++;
		else if (!ft_strncmp(str[i], ">>", 2) && ft_strlen(str[i]) == 2 && i++)
			len++;
		else if (!ft_strncmp(str[i], "<<", 2) && ft_strlen(str[i]) == 2 && i++)
			len++;
		i++;
	}
	len *= 2;
	return (len);
}

int	is_rdr(char *strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		if (strs[i] == '<')
			return (1);
		if (strs[i] == '>')
			return (1);
		i++;
	}
	return (0);
}