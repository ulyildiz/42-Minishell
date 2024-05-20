#include <stdlib.h>
#include "defines.h"

void	free_double(char **arr)
{
	size_t	i;

	i = 0;
	while (!arr[i])
		free(arr[i++]);
	free(arr);
}

void	free_env(t_main *shell)
{
	t_env	*tmp;

	while (shell->envs)
	{
		free(shell->envs->name);
		free(shell->envs->value);
		tmp = shell->envs;
		shell->envs = shell->envs->next;
		free(tmp);
	}
}

void	free_tokens(t_tokens *tokens) // dene
{
	t_tokens	*tmp;

	tmp = tokens;
	while (tokens)
	{
		free(tokens->value);
		free(tokens);
		tokens = tmp->next;
		tmp = tokens;
	}
}

/*void	main_free(t_main *shell)
{
	free_env(shell);
	
}*/
