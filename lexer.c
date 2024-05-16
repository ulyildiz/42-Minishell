#include "functions.h"
#include "42-libft/libft.h"
#include <stdlib.h>
#include <stdio.h>

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
		return (free(ipt), NULL);
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

static size_t	find_spacelen(char	*s)
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
		else if (s[i] == '\"' || s[i] == '\'')
			len += 2;
		len++;
	}
	return (len);
}

static char	*handover_spaces(char *str)
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
		else if (*str == '\"' || *str == '\'')
		{
			new_one[len++] = ' ';
			new_one[len++] = *str++;
			new_one[len++] = ' ';

		}
		else
			new_one[len++] = *str++;
	}
	return (new_one);
}
#include <errno.h> //?

static void	tilde_expendable(t_tokens *token, char *cmd_line)
{
	size_t		i;
	t_tokens	*tmp;

	tmp = token;
	i = 0;
	while (tmp)
	{
		while (cmd_line[i] != '\0' && cmd_line[i] != '~')
			i++;
		while (tmp && !ft_strnstr(tmp->value, "~", ft_strlen(tmp->value)))
			tmp = tmp->next;
		if (i != 0 && cmd_line[i] != '\0' && is_whitespace(cmd_line[i - 1]) == 1)
			tmp->is_expend = NONE_TILDE;
		if (cmd_line[i] != '\0' && is_whitespace(cmd_line[i + 1])
			&& cmd_line[i + 1] != '\0' && cmd_line[i + 1] != '/')
			tmp->is_expend = NONE_TILDE;
		if (cmd_line[i] == '\0' || !tmp)
			break;
		i++;
		tmp = tmp->next;
	}
}

void	lexer(t_main *shell)
{
	char	**arr;
	//t_tokens *t;

	arr = lex_split(handover_spaces(shell->cmd_line));
	if (!arr)
		exit(ENOMEM);//perror? // gerekli freeler okeymi kontrol et
	shell->token = tlist(arr);
	if (!shell->token)
		exit(ENOMEM);//perror?
	is_expendable(shell->token);
	tilde_expendable(shell->token, shell->cmd_line);
	//free(shell->cmd_line); //?
	//t = shell->token;
	/*while (t != NULL)
	{
		printf("lexer = %s - quote = %d - type = %d\n", t->value, t->is_expend, t->type);
		t = t->next;
	}*/
}
