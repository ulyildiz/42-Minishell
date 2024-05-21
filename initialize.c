#include <stdlib.h>
#include "functions.h"
#include "42-libft/libft.h"

static int	prompt(t_main *shell)
{
	char	*tmp;

	shell->prompt = ft_strdup("ft_sh-> ");
	if (!shell->prompt)
		return (0);
	return (1);
}

static int	init_env(t_main *shell, char **env)
{
	t_env	*tmp;
	char	**s;

	shell->envs = NULL;
	while (*env)
	{
		tmp = (t_env *)malloc(sizeof(t_env));
		if (!tmp )
			return (free_env(shell->envs), 0);
		s = ft_split(*env, '=');
		if (!s)
			return (free(tmp), free_env(shell->envs), 0);
		tmp->name = s[0];
		tmp->value = s[1];
		tmp->next = NULL;
		list_add_back(&(shell->envs), tmp);
		free(s);
		env++;
	}
	return (1);
}

int initialize(t_main *shell, char **env)
{
	if (!prompt(shell))
		return (0);
	if (!init_env(shell, env))
		return (free(shell->prompt), 0); 
    shell->paths = get_cmd(env); //execvenin arkasında yapılabilir
	if (!shell->paths)
		return (free(shell->prompt), 0);
	shell->control = 1;
	return (1);
}
