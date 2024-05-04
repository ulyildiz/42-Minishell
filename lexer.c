#include "functions.h"
#include "42-libft/libft.h"
#include <stdlib.h>
#include <stdio.h>

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
	size_t	wl;

	if (!ipt)
		return (NULL);
	i = 0;
	wc = wordcount(ipt);
	arr = (char **)ft_calloc(1 + wc, sizeof(char *));
	if (!arr)
		return (NULL);
	while (i < wc)
	{
		while ((*ipt == 32 || (9 <= *ipt && *ipt <= 13)) && *ipt != '\0')
			ipt++;
		wl = wordlen(ipt);
		arr[i] = ft_substr(ipt, 0, wl);
		ipt += wl;
		if (!arr[i])
			return (free_double(arr), NULL);
		i++;
	}
	return (arr);
}

size_t	find_spacelen(char	*s)
{
	size_t	i;
	size_t	len;

	len = 0;
	i = -1;
	while (s[++i])
	{
		if (s[i] == '|' && s[i + 1] != '|')
			len += 2;
		else if (s[i] == '<' && s[i + 1] != '<')
			len += 2;
		else if (s[i] == '>' && s[i + 1] != '>')
			len += 2;
		len++;
	}
	return (len);
}

char	*handover_spaces(char *str)
{
	char	*new_one;
	size_t	len;

	len = find_spacelen(str);
	new_one = ft_calloc(len + 1, sizeof(char));
	if (!new_one)
		return (NULL);
	len = 0;
	while (*str)
	{
		if (*str == '|')
		{
			new_one[len++] = ' ';
			new_one[len++] = *str++;
			new_one[len++] = ' ';
			while (*str == '|')
				new_one[len++] = *str++;
		}
		else if (*str == '<' || *str == '>')
		{
			new_one[len++] = ' ';
			new_one[len++] = *str++;
			if (*str == '<' || *str == '>')
				new_one[len++] = *str++;
			new_one[len++] = ' ';
		}
		new_one[len++] = *str++;
	}
	return (new_one);
}

void	lexer(t_main *shell)
{
	char	**arr;

	arr = lex_split(handover_spaces(shell->cmd_line));
	if (!arr)
		;//perror?
	free(shell->cmd_line);
	shell->token = tlist(arr);
	if (!shell->token)
		;//perror?
	//quate handle?
	/*while (shell->token != NULL)
	{
		printf("%s\n", shell->token->value);
		shell->token = shell->token->next;
	}*/
}
