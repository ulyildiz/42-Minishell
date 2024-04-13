#include "defines.h"
#include "42-libft/libft.h"
#include <stdio.h>

static char	*find_path(char **env)
{
	while (*env && ft_strncmp(*env, "PATH=", 5))
		env++;
	return ((*env) += 5);
}

char	**get_cmd(t_main *shell, char **env)
{
	char	*path;

	path = find_path(env);
	return (ft_split(path, ":"));
}


