/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:33:34 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/06/28 14:01:10 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

static size_t	lenght_to_token(t_tokens *lst)
{
	size_t	len;
	size_t	i;

	len = 0;
	while (lst && !is_token(lst))
	{
		i = 0;
		while (lst->value[i])
		{
			while (lst->value[i] && is_whitespace(lst->value[i]))
				i++;
			while (lst->value[i] && !is_whitespace(lst->value[i]))
			{
				if (lst->value[i] == '\'')
				{
					i++;
					while (lst->value[i] && lst->value[i] != '\'')
						i++;
				}	
				else if (lst->value[i] == '"')
				{
					i++;
					while (lst->value[i] && lst->value[i] != '"')
						i++;
				}
				i++;
			}
			len++;
		}
		lst = lst->next;
	}
	return (len);
}

static int	rdr_position(t_command *cmds)
{
	char	**tmp;
	size_t	i;
	size_t	j;
	size_t	f;

	i = 0;
	j = 0;
	f = 0;
	if (rdr_count(cmds->value) <= 0)
		return (0);
	while (cmds->value[i])
		i++;
	tmp = ft_calloc(i - rdr_count(cmds->value) + 1, sizeof(char *));
	if (!tmp)
		return (0);
	cmds->rdrs = ft_calloc((rdr_count(cmds->value) + 1), sizeof(char *));
	if (!cmds->rdrs)
		return (free_double(tmp), 0);
	j = 0;
	i = 0;
	while (cmds->value[i])
	{
		if (is_rdr(cmds->value[i]) == 1)
		{
			cmds->rdrs[j++] = cmds->value[i++];
			cmds->rdrs[j++] = cmds->value[i];
		}
		else
			tmp[f++] = cmds->value[i];
		i++;
	}
	free(cmds->value);
	cmds->value = tmp;
	return (1);
}

static t_command	*cmd_struct_create(t_tokens *token)
{
	t_command	*cmd;
	size_t		i;

	if (!token)
		return (NULL);
	cmd = (t_command *)ft_calloc(1, sizeof(t_command));
	if (!cmd)
		return (NULL);
	if (is_token(token))
		token = token->next;
	i = lenght_to_token(token);
	cmd->value = (char **)ft_calloc((i + 1), sizeof(char *));
	if (!cmd->value)
		return (free(cmd), NULL);
	cmd->value[i] = NULL;
	cmd->where_p = NONE_P;
	cmd->fd[0] = STDIN_FILENO;
	cmd->fd[1] = STDOUT_FILENO;
	cmd->rdrs = NULL;
	return (cmd);
}

static int handle_token(t_command **cmds, t_tokens **t, size_t *i)
{
	rdr_position(*cmds);
	*i = 0;
	(*cmds)->next = cmd_struct_create(*t);
	if (!(*cmds)->next)
		return (perror("Parser"), 0);
	(*cmds)->where_p = R_P;
	(*cmds)->next->prev = *cmds;
	*cmds = (*cmds)->next;
	(*cmds)->where_p = L_P;
	*t = (*t)->next;
	return (1);
}


char *remove_quotes(const char *str, t_bool in_s, t_bool in_d)
{
	size_t	len;
	char	*result;
	size_t	i;
	size_t	j;
	
	j = 0;
	i = 0;
	len = ft_strlen(str);
	result = (char *)ft_calloc(len + 1, sizeof(char));
	if (!result || !str)
		return (NULL);
	while (i < len)
	{
		if (str[i] == '\'' && !in_d)
		{
			in_s = !in_s;
			i++;
			continue ;
		}
		else if (str[i] == '"' && !in_s)
		{
			in_d = !in_d;
			i++;
			continue ;
		}
		result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}

static int handle_command(t_command **cmds, t_tokens **t, size_t *i)
{
	t_bool in_d;
	t_bool	in_s;
	size_t j;
	size_t f;
	size_t start;
	char *substr;
	char *cleaned_substr;

	j = 0;
	f = 0;
	in_d = FALSE;
	in_s = FALSE;
	while ((*t)->value[j])
	{
		while ((*t)->value[j] && is_whitespace((*t)->value[j]) && !in_d && !in_s)
			j++;
		start = j;
		while ((*t)->value[j])
		{
			if ((*t)->value[j] == '\'' && !in_d)
				in_s = !in_s;
			if ((*t)->value[j] == '"' && !in_s)
				in_d = !in_d;
			else if (is_whitespace((*t)->value[j]) && !in_d && !in_s)
				break;
			j++;
		}
		if (j != start)
		{
			substr = ft_substr((*t)->value, start, j - start - f);
			cleaned_substr = remove_quotes(substr, FALSE, FALSE);
			(*cmds)->value[(*i)] = cleaned_substr;
			free(substr);
			if (!(*cmds)->value[(*i)++])
				return (0);
		
		}
	}
	*t = (*t)->next;
	return (1);
}

int parser(t_main *shell, t_tokens *t, size_t i)
{
	t_command *cmds;
	
	if (shell->control == 0)
		return (1);
	cmds = cmd_struct_create(t);
	if (!cmds)
		return (perror("Parser"), 0);
	shell->cmd = cmds;
	while (t)
	{
		if (!is_token(t))
		{
			if (!handle_command(&cmds, &t, &i))
				return (0);
		}
		else
		{
			if (!handle_token(&cmds, &t, &i))
				return (0);
		}
	}
	rdr_position(cmds);
	cmds->next = NULL;
	return (free_tokens(shell), 1);
}

/* 	t_command *tmp = shell->cmd;
	while (tmp)
	{
		i = 0;
		while (tmp->value[i])
		{
			printf("/%s/", tmp->value[i]);
			i++;
		}
		printf("\n");
		printf("/where_p = %d - where_r = %d\n", tmp->where_p, tmp->where_r);
		if(tmp)
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
		printf("value = %s - prev = %p - next = %p\n", shell->cmd->value[0],
				shell->cmd->prev, shell->cmd->next);
		shell->cmd = shell->cmd->next;
	} */