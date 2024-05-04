#include "functions.h"
#include "42-libft/libft.h"
#include <stdlib.h>

static t_token_types	identify_t(char	*arr)
{
	if (ft_strlen(arr) == 1 && *arr == '|')
		return (PIPE);
	else if (ft_strlen(arr) == 1 && (*arr == '<' || *arr == '>'))
		return (RDR);
	else if (ft_strlen(arr) == 2 && (ft_strnstr(arr, "<<", 2) || ft_strnstr(arr, ">>", 2)))
		return (RDR);
	return (CMD);
}

int	token_add_back(t_tokens **list, t_tokens *new)
{
	t_tokens	*tmp;

	tmp = *list;
	if (!new)
		return (0);
	if (!*list)
		*list = new;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (1);
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
#include <stdio.h>
t_tokens	*tlist(char **arr)
{
	t_tokens	*linked;
	size_t		i;

	i = 0;
	linked = NULL;
	while (arr[i])
		if (!token_add_back(&linked, create_token(arr[i++])))
			return (NULL);
	return (linked);
}