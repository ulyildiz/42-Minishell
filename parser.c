#include "functions.h"
#include "42-libft/libft.h"
#include <stdlib.h>
#include <unistd.h>

int	is_token(t_token_types type)
{
	if (type == PIPE || type == RDR_IN
		|| type == RDR_OUT || type == HEREDOC)
		return (1);
	return (0);
}

static size_t	lenght_to_token(t_tokens *lst)
{
	size_t	len;

	len = 0;
	while (!is_token(lst->type))
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

	cmd = (t_command *)ft_calloc(1, sizeof(t_tokens));
	if (!cmd)
		return (NULL);
	i = lenght_to_token(token);
	cmd->value = (char **)malloc(i * sizeof(char *));
	if (!cmd->value)
		return (free(cmd), NULL);
	cmd->value[i] == NULL;
	cmd->infile = STDIN_FILENO/*0*/;
	cmd->outfile = STDOUT_FILENO/*1*/;

	return (cmd);
}

void	parser(t_main *shell)
{
	t_command	*cmd;
	t_tokens	*t;
	size_t		i;

	t = shell->token;
	shell->cmd = cmd_struct_create(t);
	if (!shell->cmd)
		return /*hata mesajı*/;
	cmd = shell->cmd;
	while (t)
	{
		i = 0;
		while (!is_token(t))
		{
			cmd->value[i] = ft_strdup(t->value);
			if (!cmd->value[i])
				/*freeler*/;
			
			i++;
		}
		t = t->next;
		cmd = cmd->next;
	}
}
