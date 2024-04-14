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

char	**get_cmd(char **env)
{
	while (*env && ft_strncmp(*env, "PATH=", 5))
		env++;
	return (ft_split((*env) += 5, ':'));
}

int	is_space(char *s) //spaceleri geçme
{
	int	i;

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
