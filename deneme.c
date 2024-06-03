#include <stdlib.h>

int main()
{
	char *a = calloc(5, 5);

	a[2] = 'a';
	free(a);
}