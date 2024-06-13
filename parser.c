/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:33:34 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/06/13 23:21:35 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42-libft/libft.h"
#include "functions.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	is_token(t_tokens *t)
{
	if (t->type == PIPE && (t->is_expend != WITHIN_D_Q
			&& t->is_expend != WITHIN_Q))
		return (1);
	return (0);
}

static size_t	lenght_to_token(t_tokens *lst)
{
	size_t	len;
	size_t	i;

	len = 0;
	while (lst && !is_token(lst))
	{
		i = 0;
		while (lst && lst->is_expend != NONE)
		{
			lst = lst->next;
			if (lst && lst->is_expend == NONE)
				len++;
		}
		while (lst && lst->value[i])
		{
			while (lst->value[i] && is_whitespace(lst->value[i]))
				i++;
			while (lst->value[i] && !is_whitespace(lst->value[i]))
				i++;
			len++;
			while (lst->value[i] && is_whitespace(lst->value[i]))
				i++;
		}
		if (lst)
			lst = lst->next;
	}
	return (len);
}

size_t	rdr_count(char **str)
{
	size_t	len;
	size_t	i;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (!ft_strncmp(str[i], "<", 1) && ft_strlen(str[i]) == 1)
			len++;
		else if (!ft_strncmp(str[i], ">", 1) && ft_strlen(str[i]) == 1)
			len++;
		else if (!ft_strncmp(str[i], ">>", 2) && ft_strlen(str[i]) == 2)
			len++;
		i++;
	}
	len *= 2;
	return (len);
}

int	is_rdr(char *strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		if (strs[i] == '<')
			return (1);
		if (strs[i] == '>')
			return (1);
		i++;
	}
	return (0);
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
	if (cmds->rdrs == NULL)
		return (0);
	while (cmds->value[i])
		i++;
	tmp = ft_calloc(i - rdr_count(cmds->value) + 1, sizeof(char *));
	if (!tmp)
		return (0);
	cmds->rdrs = ft_calloc((rdr_count(cmds->value) + 1), sizeof(char *));
	if (!cmds->rdrs)
		return (free(tmp), 0);
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
	cmd->value = (char **)ft_calloc((i + 1) , sizeof(char *));
	if (!cmd->value)
		return (free(cmd), NULL);
	cmd->value[i] = NULL;
	cmd->where_p = NONE_P;
	cmd->where_r = NONE_RDR;
	cmd->fd[0] = STDIN_FILENO;
	cmd->fd[1] = STDOUT_FILENO;
	cmd->rdrs = NULL;
	return (cmd);
}

/* char	*identifier_check(t_tokens *t, char **s)
{
	if (ft_strnstr(t->value,))

	return (NULL);
} */

int	arrange_split(t_command *cmds, t_tokens *t, size_t *i)
{
	char	**ar;
	size_t	j;

	j = 0;
	ar = ft_split(t->value, ' ');
	if (!ar)
		return (0);
/* 	if (ft_strncmp(ar[0], "export", ft_strlen(ar[0]))) // küçük harf yapma fonksiyonunu koy ar[0]a & " || ft_strncmp(ar[0], "env", ft_strlen(ar[0])" env export ile synı hatayı vermiyor
	{
		if ()
	} */
	while (ar[j])
		cmds->value[(*i)++] = ar[j++];
	return (free(ar), 1);
}

int	parser(t_main *shell, t_tokens *t, size_t i)
{
	t_command	*cmds;
	size_t		j;

	j = 0;
	if (!t || shell->control == 0)
		return (1);
	cmds = cmd_struct_create(t);
	if (!cmds)
		return (perror("Parser"), 0);
	shell->cmd = cmds;
	while (t)
	{
		if (t && !is_token(t))
		{
			if (t->is_expend == NONE)
				arrange_split(cmds, t, &i);
			else
				cmds->value[i++] = ft_strdup(t->value);
		}
		else if (t && is_token(t))
		{
			rdr_position(cmds);
			i = 0;
			cmds->next = cmd_struct_create(t);
			if (!cmds->next)
				return (perror("Parser"), 0);
			cmds->where_p = R_P;
			cmds->next->prev = cmds;
			cmds = cmds->next;
			cmds->where_p = L_P;
		}
		if (t)
			t = t->next;
	}
	cmds->next = NULL;
	rdr_position(cmds);
	return (1);
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