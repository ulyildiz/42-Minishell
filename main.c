#include <stdio.h>
#include "functions.h"
#include "42-libft/libft.h"

int	main(int ac, char** av, char **env)
{
	t_main	shell;

	//signal_reciever();
	av = (void *)av;
	if (ac >=2)
		return(ft_putstr_fd("Too much argument.", 2), 1);
	if (!initialize(&shell, env))
		return (perror("Initialize"), 1);
	start_shell(&shell);
	main_free(&shell);
    return (0);
}