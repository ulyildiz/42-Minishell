#include "functions.h"
#include "42-libft/libft.h"
#include <stdlib.h>

static t_token_types	identify_t(char	*arr)
{
	
}

void	token_add_back(t_tokens *list, t_tokens *new)
{
	if (!list)
		list = new;
	else
	{
		while (list->next != NULL)
			list = list->next;
		list->next = new;
	}
}

t_tokens	*create_token(char	*arr)
{
	t_tokens	*new;

	new = (t_tokens *)ft_calloc(1, sizeof(t_tokens));
	if (!new)
		return (NULL);
	new->value = arr;
	new->type = identify_t(arr);
	return (new);
}
