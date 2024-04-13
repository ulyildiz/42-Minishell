#include "defines.h"
#include "functions.h"

//değişken atamaları
int initialize(t_main *shell, char **env)
{
    shell->paths = get_cmd(shell, env);
	if (!shell->paths)
		return (0);

	return (1);
}
