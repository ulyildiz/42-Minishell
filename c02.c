#include <stdio.h>
int main()
{
    int i = 190;

    int *a = &i;

    printf("i = %d - a = %d, &i = %d - *a = %d", i, *a, &i, a);
}