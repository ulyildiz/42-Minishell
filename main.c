#include <stdio.h>
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
        printf("%s\n",env[ac++]);
    }
    
    return (0);
}