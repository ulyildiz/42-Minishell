

#include "functions.h"

void	pwd(t_command *cmds, t_main *shell)
{
	char	*pwd;

	shell = (void *)shell;
	pwd = getcwd(NULL, 0);
	if (pwd != NULL)
		ft_putendl_fd(pwd, cmds->fd[1]);
	else
		ft_putendl_fd("pwd not set", cmds->fd[1]);
	free(pwd);
	//d0nE
}
