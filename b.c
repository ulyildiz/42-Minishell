#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{   
    printf("%d\n",chdir(".."));
    printf("%d\n",chdir("-"));
    system("cd -");
    return(1);
}