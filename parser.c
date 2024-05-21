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

static void	token_position(t_command *cmds, t_tokens *t)
{
	for_prev(cmds->prev, t->type);
	for_itself(cmds, t->type);
}

static t_command *cmd_struct_create(t_tokens *token)
{
	t_command	*cmd;
	size_t		i;

	if (!token)
		return (NULL);
	cmd = (t_command *)ft_calloc(1, sizeof(t_command));
	if (!cmd)
		return (NULL);
	if (is_token(token->type))
		token = token->next;
	i = lenght_to_token(token);
	cmd->value = (char **)malloc((i + 1) * sizeof(char *));
	if (!cmd->value)
		return (free(cmd), NULL);
	cmd->value[i] = NULL;
	cmd->where_p = NONE_P;
	cmd->where_r = NONE_RDR;
	cmd->infile = STDIN_FILENO;
	cmd->outfile = STDOUT_FILENO;
	return (cmd);
}

int	parser(t_main *shell, t_tokens *t, size_t i)
{
	t_command	*cmds;
//	t_command *tmp;

	if (shell->control == 0)
		return (1);
	cmds = cmd_struct_create(t);
	if (!cmds)
		return (perror("Parser"), 0);
	shell->cmd = cmds;
	while (t)
	{
		if (!is_token(t->type))
			cmds->value[i++] = t->value;	
		else if (is_token(t->type))
		{
			i = 0;
			cmds->next = cmd_struct_create(t);
			if (!cmds->next)
				return (perror("Parser"), 0); // freeler
			cmds->next->prev = cmds;
			cmds = cmds->next;
			token_position(cmds, t);
		}
		t = t->next;	
	}
	return (1);
}

/* 	tmp = shell->cmd;
	while (tmp)
	{
		i = 0;
	//	write(2, "x", 1);
		while (tmp->value[i])
		{
			printf("%s ", tmp->value[i]);
			i++;
		}
		printf("where_p = %d - where_r = %d\n", tmp->where_p, tmp->where_r);
		tmp = tmp->next;
		
	} */
/* 		i = 0;
		while (t && !is_token(t->type))
		{
			cmds->value[i++] = t->value;
			t = t->next;
		}
		if (t)
			t = t->next;
		cmds->next = cmd_struct_create(t);
		if (cmds->next)
			cmds->next->prev = cmds;
		cmds = cmds->next; */

/* 	while (shell->cmd)
	{
		printf("value = %s - prev = %p - next = %p\n", shell->cmd->value[0], shell->cmd->prev, shell->cmd->next);
		shell->cmd = shell->cmd->next;
	} */