#include <stdio.h>

size_t	wordcount(char *s)
{
	size_t	wc;

	wc = 0;
	while (*s && s)
	{
		while (*s && (*s == 32 || (9 <= *s && *s <= 13)))
			s++;
		while (*s && !(*s == 32 || (9 <= *s && *s <= 13)))
			s++;
		wc++;
	}
	return (wc);
}


int main()
{
	printf("%zu\n", wordcount("\n\tağla\n\nmerhaba\rnasılsın\ngerzek"));
}