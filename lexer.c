#include "functions.h"
#include "42-libft/libft.h"
#include <stdlib.h>

static size_t	wordlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len] && !(str[len] == 32 || (9 <= str[len] && str[len] <= 13)))
		len++;
	return (len);
}

static char	**lex_split(char *ipt)
{
	char	**arr;
	size_t	i;
	size_t	wc;

	i = 0;
	wc = wordcount(ipt);
	arr = (char **)ft_calloc(1 + wc, sizeof(char *));
	if (!arr)
		return (NULL);
	while (i < wc)
	{
		while (*ipt == 32 || (9 <= *ipt && *ipt <= 13))
			ipt++;
		arr[i] = ft_substr(ipt, 0, wordlen(ipt));
		if (!arr[i])
			return (free_double(arr), NULL);
		i++;
	}
	return (arr);
}

static t_tokens	*tlist(char **arr)
{
	t_tokens	*linked;
	size_t		i;

	i = 0;
	while (arr[i])
		token_add_back(linked, create_token(arr[i++]));
	return (linked);
}

void	lexer(t_main *shell)
{
	char	**arr;

	//whitespacelere göre splitlere
	arr = lex_split(shell->cmd_line);
	if (!arr)
		/**/;
	//token listesi oluştur
	shell->token = tlist(arr);
	if (!shell->token)
		/**/;
	//syntax kontrolu? "expanderın sonunda da olabilir"
}
