#include <stdlib.h>
#include "functions.h"
#include "42-libft/libft.h"

static int	init_env(t_main *shell, char **env)
{
	t_env	*tmp;
	char	**s;
	
	shell->envs = NULL;
	while (*env)
	{
		tmp = (t_env *)malloc(sizeof(t_env));
		if (!tmp)
			return (0);
		s = ft_split(*env, '=');
		if (!s)
			return (0);
		tmp->name = s[0];
		tmp->value = s[1];
		tmp->next = NULL;
		list_add_back(&(shell->envs), tmp);
		env++;
	}
	return (1);
}

//değişken atamaları
int initialize(t_main *shell, char **env)
{
	if (!init_env(shell, env))
		return (/*list_free*/0);
    shell->paths = get_cmd(env);
	if (!shell->paths)
		return (/*list_free*/0);

	return (1);
}
