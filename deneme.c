// Online C compiler to run C program online
#include <stdio.h>

int main() {
    // Write C code here
    int i;
    
    i = 0;
    while(i < 10)
    {
        printf("%d\n", ~(i % 2));
        i++;
    }
    return 0;
} 