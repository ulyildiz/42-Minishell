
#include "functions.h"

void	pwd(t_command *cmds, t_main *shell)
{
	char *pwd;
	
	pwd = getcwd(NULL, 0);
	if (pwd != NULL)
	{
		ft_putstr_fd(pwd, cmds->fd[1]);
		ft_putstr_fd("\n", cmds->fd[1]);
	}
	else
	{
		ft_putstr_fd("pwd not set", cmds->fd[1]);
		ft_putstr_fd("\n", cmds->fd[1]);
	}
	free(pwd);
	//d0nE
}