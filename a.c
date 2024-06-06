#include <stdlib.h>
#include <stdio.h>

int main()
{
	char **a = (char **)malloc(2 * sizeof(char *));

	a[1] = NULL;

	//free(a[0]);
	free(a);
}