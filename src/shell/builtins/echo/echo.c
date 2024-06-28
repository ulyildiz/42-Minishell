
#include "functions.h"

void	echo(t_command *cmds, t_main *shell)
{
	size_t	i;
	size_t	j;
	int		newline;

	i = 1;
	newline = 1;
	if (cmds->value[i] && cmds->value[i][0] == '-')
	{
		while (cmds->value[i] && cmds->value[i][0] == '-')
		{
			j = 1;
			while (cmds->value[i][j] == 'n')
				j++;
			if (cmds->value[i][j] == '\0')
				newline = 0;
			else
				break ;
			i++;
		}
	}
	if (cmds->value[i])
		ft_putstr_fd(cmds->value[i++], cmds->fd[1]);
	while (cmds->value[i])
	{
		ft_putstr_fd(" ", cmds->fd[1]);
		ft_putstr_fd(cmds->value[i++], cmds->fd[1]);
	}
	if (newline)
		ft_putstr_fd("\n", cmds->fd[1]);
}