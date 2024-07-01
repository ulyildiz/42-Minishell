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

#include "functions.h"

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
	char	**path;
	char	**path2;
	t_env	*tmp;
	int		i;

	i = 0;
	path = NULL;
	tmp = find_env(env, "PATH");
	if (tmp)
	{
		path = ft_split(tmp->value, ':');
		if (!path)
			return (perror("Path init 1"), NULL);
		while (path[i] != NULL)
			i++;
	}
	path2 = (char **)ft_calloc(i + 2, sizeof(char *));
	if (!path2)
		return (perror("Path init 2"), free_double(path), NULL);
	i = -1;
	if (path)
	{
		while (path[++i] != NULL)
			path2[i] = path[i];
		free(path);
	}
	else
		++i;
	tmp = find_env(env, "PWD");
	if (tmp)
	{
		path2[i] = ft_strdup(tmp->value);
		if (!path2[i])
			return (perror("Path init 3"), free_double(path2), NULL);
	}
	return (path2);
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
