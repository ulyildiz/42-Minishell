
#include "functions.h"

int	is_builtin(t_command *cmds, t_main *shell)
{
	int				i;
	static t_build	commands[] = {{"echo", echo}, {"cd", cd}, {"pwd", pwd},
			{"env", env}, {"unset", unset}, {"export", export}, {"exit",
			exit_cmd}, {NULL, NULL}};

	i = 0;
	while (commands[i].name)
	{
		if (ft_strncmp(ft_strlower(cmds->value[0]), commands[i].name,
				ft_strlen(cmds->value[0])) == 0)
		{
			commands[i].func(cmds, shell);
			return (1);
		}
		i++;
	}
	return (0);
}