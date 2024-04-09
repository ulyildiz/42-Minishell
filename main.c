#include <stdio.h>
#include <string.h>
#include "defines.h"

int main (int ac, char** av, char **env)
{
    t_main  shell;

    if (ac >=2)
        return(printf("Wrong Argument"));
    //if (initialize(&shell))
    //    return (printf("Couldn't initialize"), 1);
    //signal
    //start_shell(&shell);
    ac = 0;
    while (env[ac])
    {
        if (strncmp("PATH",env[ac],4) == 0)
        {
            printf("%s\n",env[ac]);   
        }
        ac++;
    }
    
    return (0);
}