/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 21:04:48 by ysarac            #+#    #+#             */
/*   Updated: 2024/07/12 17:00:40 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
static int	dollar_expend(t_main *shell, char** cmd, char *tmp, size_t i)
{
	size_t	start;

	tmp = ft_strdup("");
	while ((*cmd)[i])
	{
		if ((*cmd)[i] == '$' && !shell->in_s)
			tmp = handle_dollar_sign(tmp, *cmd, &i, shell);
		else
		{
			start = i;
			while ((*cmd)[i] && !((*cmd)[i] == '$' && !shell->in_s))
			{
				toggle_quote((*cmd)[i], &shell->in_s, &shell->in_d);
				i++;
			}
			tmp = append_literal(tmp, *cmd, &start, &i);
		}
		if (!tmp)
			return (perror("Dollar Expend"), 0);
	}
	return (free(*cmd), *cmd = tmp, 1);
}

static int	home_expend(t_main *shell, char** cmd, char *tmp, size_t i)
{
	tmp = ft_strdup("");
	while ((*cmd)[i] && tmp)
	{
		if ((*cmd)[i] == '~' && !shell->in_s && !shell->in_d)
		{
			if ((i > 0 && !is_whitespace((*cmd)[i - 1])) || \
			(!is_whitespace((*cmd)[i + 1]) && (*cmd)[i + 1] != '\0'
					&& (*cmd)[i + 1] != '/'))
				tmp = ft_strappend(tmp, "~", 1);
			else
			{
				if (!find_env(shell->envs, "HOME"))
					return (1);
				tmp = ft_strappend(tmp, find_env(shell->envs, "HOME")->value,
						ft_strlen(find_env(shell->envs, "HOME")->value));
			}
		}
		else
			tmp = ft_strappend(tmp, &(*cmd)[i], 1);
		toggle_quote((*cmd)[i], &shell->in_s, &shell->in_d);
		i++;
	}
	if (!tmp)
		return (perror("Home expand"), 0);
	return (free(*cmd), *cmd = tmp, 1);
}
extern char	**recreate_cmdval(t_command *cmd);

char	*remove_quotes(const char *str, t_bool in_s, t_bool in_d)
{
	char	*result;
	size_t	i;
	size_t	j;

	if (!str)
		return (NULL);
	result = allocate_result(str);
	if (!result)
		return (NULL);
	j = 0;
	i = 0;
	while (str[i])
	{
		toggle_quote(str[i], &in_s, &in_d);
		if ((str[i] == '\'' && !in_d) || (str[i] == '"' && !in_s))
		{
			i++;
			continue ;
		}
		result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}

void	expender(t_main *shell)
{
	t_command	*cmds;
	size_t		i;

	if (shell->control == 0)
		return ;
	cmds = shell->cmd;
	while (cmds)
	{
		i = -1;
		shell->in_d = FALSE;
		shell->in_s = FALSE;
		while (cmds->value[++i])
		{
			if (ft_strnstr(cmds->value[i], "$", ft_strlen(cmds->value[i])))
			{
				if (!dollar_expend(shell, &cmds->value[i], NULL, 0))
					return (exit_in_lex_ex(shell));
			}
			if (ft_strnstr(cmds->value[i], "~", ft_strlen(cmds->value[i])))
			{
				if (!home_expend(shell, &cmds->value[i], NULL, 0))
					return (exit_in_lex_ex(shell));		
			}
		}
		cmds->value = recreate_cmdval(cmds);
		printf("a\n");
		i = -1;
		shell->in_d = FALSE;
		shell->in_s = FALSE;
		while (cmds->rdrs && cmds->rdrs[i += 2])
		{
			if (ft_strnstr(cmds->rdrs[i], "$", ft_strlen(cmds->rdrs[i])))
			{
				if (!dollar_expend(shell, &cmds->rdrs[i], NULL, 0))
					return (exit_in_lex_ex(shell));
			}
			if (ft_strnstr(cmds->rdrs[i], "~", ft_strlen(cmds->rdrs[i])))
			{
				if (!home_expend(shell, &cmds->rdrs[i], NULL, 0))
					return (exit_in_lex_ex(shell));
			}
			cmds->rdrs[i] = remove_quotes(cmds->rdrs[i], FALSE, FALSE);
		}
		cmds = cmds->next;
	}
}
