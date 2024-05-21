#include "functions.h"
#include "42-libft/libft.h"
#include <stdlib.h>

static t_token_types	identify_t(const char *arr)
{
	if (ft_strlen(arr) == 1 && *arr == '|')
		return (PIPE);
	else if (ft_strlen(arr) == 1 && *arr == '<' )
		return (RDR_OUT);
	else if (ft_strlen(arr) == 2 && ft_strnstr(arr, "<<", 2))
		return (HEREDOC);
	else if (ft_strlen(arr) == 2 && ft_strnstr(arr, ">>", 2))
		return (RDR_IN);
	else if (ft_strlen(arr) == 2 && ft_strnstr(arr, "<>", 2))
		return (RDR_OUT);
	else if (ft_strlen(arr) == 1 && *arr == '>')
		return (RDR_IN);
	else if (*arr == '\'')
		return (QUOTE);
	else if (*arr == '\"')
		return (D_QUOTE);
	return (CMD);
}

static int	token_add_back(t_tokens **list, t_tokens *new)
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

void	is_expendable(t_tokens *lst)
{
	t_tokens	*tmp;

	tmp = lst;
	while (tmp)
	{
		while (tmp && (tmp->type != D_QUOTE && tmp->type != QUOTE))
			tmp = tmp->next;
		if (tmp && tmp->type == D_QUOTE && tmp->is_expend == NONE)
		{
			lst = tmp->next;
			tmp = tmp->next;
			while (tmp && tmp->type != D_QUOTE)
				tmp = tmp->next;
			while (tmp && lst && lst != tmp)
			{
				lst->is_expend = WITHIN_D_Q;
				lst = lst->next;
			}
		}
		else if (tmp && tmp->type == QUOTE && tmp->is_expend == NONE)
		{
			lst = tmp->next;
			tmp = tmp->next;
			while (tmp && tmp->type != QUOTE)
				tmp = tmp->next;
			while (tmp && lst && lst != tmp)
			{
				lst->is_expend = WITHIN_Q;
				lst = lst->next;
			}
		}
		if (tmp)
			tmp = tmp->next;
	}
}

static t_tokens	*create_token(char	*arr)
{
	t_tokens	*new;

	new = (t_tokens *)ft_calloc(1, sizeof(t_tokens));
	if (!new)
		return (NULL);
	new->value = arr;
	new->is_expend = NONE;
	new->type = identify_t(arr);
	return (new);
}

t_tokens	*tlist(char **arr)
{
	t_tokens	*linked;
	size_t		i;

	i = 0;
	linked = NULL;
	while (arr[i])
		if (!token_add_back(&linked, create_token(arr[i++]))) // arr 0 iken hata olursa freelemk bozar mı
			return (free_tokens(linked), NULL);
	return (linked);
}
