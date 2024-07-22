/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarac <ysarac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 12:43:09 by ysarac            #+#    #+#             */
/*   Updated: 2024/07/01 13:18:09 by ysarac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "libft.h"

void	list_add_back(t_env **lst, t_env *tmp)
{
	t_env	*last;

	if (!tmp)
		return ;
	if (!*lst)
		*lst = tmp;
	else
	{
		last = *lst;
		while (last->next)
			last = last->next;
		last->next = tmp;
	}
}

size_t	wordlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len] && !(str[len] == 32 || (9 <= str[len] && str[len] <= 13)))
		len++;
	return (len);
}

char	**get_cmd(t_env *env)
{
	while (env && ft_strncmp(env->name, "PATH", 4))
		env = env->next;
	if (!env)
		return (ft_split("", '\0'));
	return (ft_split(env->value, ':'));
}

int	is_whitespace(char c)
{
	if (c == 32 || (9 <= c && c <= 13))
		return (1);
	return (0);
}

size_t	t_lst_size(t_tokens *t)
{
	size_t	len;

	len = 0;
	while (t)
	{
		len++;
		t = t->next;
	}
	return (len);
}
