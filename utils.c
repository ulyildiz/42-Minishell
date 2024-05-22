#include "defines.h"
#include "42-libft/libft.h"
#include <stdio.h>

void	list_add_back(t_env **lst, t_env *tmp)
{
	t_env	*last;

	if (!tmp)
		return;
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

char	**get_cmd(char **env)
{
	while (*env && ft_strncmp(*env, "PATH=", 5))
		env++;
	return (ft_split((*env) += 5, ':'));
}

size_t	is_space(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] == ' ')
		i++;
	if (s[i] == '\0')
		return (0);
	return (1);
}

t_env	*find_env(t_env *envs, char *wanted)
{
	while(envs)
	{
		if (!ft_strncmp(envs->name, wanted, ft_strlen(wanted)))
			return (envs);
		envs = envs->next;
	}
	return (NULL);
}

size_t	wordcount(char *s)
{
	size_t	wc;

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
	if (!(c == ' ' || (9 <= c && c <= 13)))
		return (1);
	return (0);
}