#include <stdio.h>
#include <string.h>
#include "functions.h"

int	main(int ac, char** av, char **env)
{
	t_main	shell;

	//signal_reciever();
	av = (void *)av;
	if (ac >=2)
		return(printf("Wrong Argument"), 1);
	if (!initialize(&shell, env))
		return (printf("Couldn't initialize"), 1);
	start_shell(&shell);
    
    return (0);
}