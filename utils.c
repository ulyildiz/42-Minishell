#include "defines.h"
#include "42-libft/libft.h"
#include <stdio.h>

char	**get_cmd(t_main *shell, char **env)
{
	while (*env && ft_strncmp(*env, "PATH=", 5))
		env++;
	return (ft_split((*env) += 5, ":"));
}
