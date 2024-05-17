#include "functions.h"
#include "42-libft/libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int	is_token(t_token_types type)
{
	if (type == PIPE || type == RDR_IN
		|| type == RDR_OUT || type == HEREDOC)
		return (1);
	return (0);
}

static void	remove_quotes(t_tokens **token)
{
	t_tokens	*tmp;
	t_tokens	*tmp2;

	tmp2 = *token;
	while (tmp2 && tmp2->next)
	{
		if (tmp2->next->is_expend == NONE &&
			(tmp2->next->type == QUOTE || tmp2->next->type == D_QUOTE))
		{
			tmp = tmp2->next;
			tmp2->next = tmp->next;
			free(tmp->value);
			free(tmp);
		}
		tmp2 = tmp2->next;
	}
}

static size_t	lenght_to_token(t_tokens *lst)
{
	size_t	len;

	len = 0;
	while (lst && !is_token(lst->type))
	{
		lst = lst->next;
		len++;
	}
	return (len);
}

static t_command *cmd_struct_create(t_tokens *token)
{
	t_command	*cmd;
	size_t		i;

	if (!token || token == NULL)
		return (NULL);
	cmd = (t_command *)ft_calloc(1, sizeof(t_tokens));
	if (!cmd)
		return (NULL);
	i = lenght_to_token(token);
	cmd->value = (char **)malloc((i + 1) * sizeof(char *));
	if (!cmd->value)
		return (free(cmd), NULL);
	cmd->value[i] = NULL;
	cmd->infile = STDIN_FILENO;
	cmd->outfile = STDOUT_FILENO;
	return (cmd);
}

void	parser(t_main *shell)
{
	t_command	*cmds;
	t_tokens	*t;
	size_t		i;

	t = shell->token;
	remove_quotes(&t);
	cmds = cmd_struct_create(t);
	if (!cmds)
		return /*hata mesajı*/;
	shell->cmd = cmds;
	while (t)
	{
		i = 0;
		while (t && !is_token(t->type))
		{
			cmds->value[i] = t->value;
			printf("%s - %s\n", cmds->value[i], t->value);
			i++;
			t = t->next;
		}
		if (t)
			t = t->next;
		printf("-%s- -%p-\n", cmds->value[0], cmds->value[0]);
		cmds->next = cmd_struct_create(t);
		printf("-%s- -%p-\n", cmds->value[0], cmds->value[0]);
		if (cmds->next)
			cmds->next->prev = cmds;
		cmds = cmds->next;
	}
	printf("\n");
//	printf("-%s-\n", shell->cmd->value[1]);
/* 	while (shell->cmd)
	{
		i = 0;
	//	write(2, "x", 1);
		while (shell->cmd->value[i])
		{
			printf("value[i] = %s\n ", shell->cmd->value[i]);
			i++;
		}
		printf("prev = %p - next = %p\n", shell->cmd->prev, shell->cmd->next);
		shell->cmd = shell->cmd->next;
		
	} */
}


	/*while (shell->cmd)
	{
		printf("prev = %p - next = %p\n", shell->cmd->prev, shell->cmd->next);
		shell->cmd = shell->cmd->next;
	}*/