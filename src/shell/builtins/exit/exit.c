
#include "functions.h"

void	exit_cmd(t_command *cmds, t_main *shell)
{	
	shell = (void *)shell;
	ft_putstr_fd("exit", cmds->fd[1]);
	ft_putstr_fd("\n", cmds->fd[1]);
	/*
	free işlemleri yapılacak
	ama bu kısmı projenin sonuna bırakıyorum
	*/
	exit(0);
}
