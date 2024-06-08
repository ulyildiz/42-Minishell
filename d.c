#include <stdio.h>

void    a(int *i)
{
    ++(*i);
}

int main()
{
    int i = 0;
    a(&i);
    printf("%d\n", i);
}