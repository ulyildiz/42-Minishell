#include <stdio.h>
#include <string.h>
#include "functions.h"

int main (int ac, char** av, char **env)
{
    t_main  shell;
	
	av = (void *)av;
    if (ac >=2)
        return(printf("Wrong Argument"));
    if (!initialize(&shell, env))
        return (printf("Couldn't initialize"), 1);
    signal_reciever();
    //start_shell(&shell);
    /*ac = 0;
    while (env[ac])
    {
        if (strncmp("PATH",env[ac],4) == 0)
        {
            printf("%s\n",env[ac]);   
        }
        ac++;
    }*/
    
    return (0);
}