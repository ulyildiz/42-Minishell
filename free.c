#include <stdlib.h>
#include "defines.h"

void	free_double(char **arr)
{
	size_t	i;

	i = 0;
	while (arr && arr[i])
		free(arr[i++]);
	free(arr);
}

void free_env(t_env *env)
{
	t_env *tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		if (tmp->name)
			free(tmp->name);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}

void	free_tokens(t_tokens *tokens)
{
	t_tokens	*tmp;

	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}

void	main_free(t_main *shell)
{
	free_env(shell->envs);
	free_tokens(shell->token);
	free_double(shell->paths);
	free(shell->prompt);
	free(shell->cmd_line);
	
}
