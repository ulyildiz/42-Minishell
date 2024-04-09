#include <stdio.h>

int main (int ac, char** av, char **env)
{
    if (ac >=2)
        return(printf("Wrong Argument"));
    ac = 0;
    while (env[ac])
    {
        printf("%s\n",env[ac++]);
    }
    
    return (0);
}