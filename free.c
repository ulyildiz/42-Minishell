#include <stdlib.h>
#include "defines.h"

void	free_double(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	free_env(t_env *env)
{
	t_env *tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->name);
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

void	free_command(t_command *cmd)
{
	t_command	*tmp;

	while(cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		if (tmp->value)
			free_double(tmp->value);
		free(tmp);
	}
}

void	main_free(t_main *shell)
{
	free_env(shell->envs);
	free_tokens(shell->token);
	free_command(shell->cmd);
	free_double(shell->paths);
	free(shell->prompt);
	free(shell->cmd_line);
}
