/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:27:15 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/06/24 14:27:15 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42-libft/libft.h"
#include "functions.h"
#include <stdio.h>

void	list_add_back(t_env **lst, t_env *tmp)
{
	t_env *last;

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
	size_t len;

	len = 0;
	while (str[len] && !(str[len] == 32 || (9 <= str[len] && str[len] <= 13)))
		len++;
	return (len);
}

char	**get_cmd(t_env *env)
{
	char **path;
	char **path2;
	int i;

	i = 0;
	path = ft_split(find_env(env, "PATH")->value, ':');
	if (!path)
		return (perror("Path init 1"), NULL);
	while (path[i] != NULL)
		i++;
	path2 = (char **)ft_calloc(i + 2, sizeof(char *));
	if (!path2)
		return (perror("Path init 2"), free_double(path), NULL);
	i = -1;
	while (path[++i] != NULL)
		path2[i] = path[i];
	free(path);
	path2[i] = ft_strdup(find_env(env, "PWD")->value);
	if (!path2[i])
		return (perror("Path init 3"), free_double(path2), NULL);
	return (path2);
}

size_t	is_space(char *s)
{
	size_t i;

	i = 0;
	while (s[i] && s[i] == ' ')
		i++;
	if (s[i] == '\0')
		return (0);
	return (1);
}

t_env	*find_env(t_env *envs, char *wanted)
{
	size_t	l;
	
	l = ft_strlen(wanted);
	while (envs)
	{
		if (!ft_strncmp(envs->name, wanted, l) &&
			!ft_strncmp(envs->name, wanted, ft_strlen(envs->name)))
			return (envs);
		envs = envs->next;
	}
	return (NULL);
}

size_t	wordcount(char *s)
{
	size_t wc;

	wc = 0;
	while (*s && s)
	{
		while (*s != '\0' && (*s == 32 || (9 <= *s && *s <= 13)))
			s++;
		if (*s != '\0' && !(*s == 32 || (9 <= *s && *s <= 13)))
			wc++;
		while (*s != '\0' && !(*s == 32 || (9 <= *s && *s <= 13)))
			s++;
	}
	return (wc);
}

int	is_whitespace(char c)
{
	if (c == 32 || (9 <= c && c <= 13))
		return (1);
	return (0);
}

size_t	t_lst_size(t_tokens *t)
{
	size_t len;

	len = 0;
	while (t)
	{
		len++;
		t = t->next;
	}
	return (len);
}

void	syntax_message(int flag)
{
	if (flag == 1)
		ft_putstr_fd("Syntax error near unexpected pipe token\n", 2);
	else if (flag == 2)
		ft_putstr_fd("Syntax error near unexpected redirection token\n", 2);
	else if (flag == 3)
		ft_putstr_fd("Syntax error unclosed quote.\n", 2);
}
