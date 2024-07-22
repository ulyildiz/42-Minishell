/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 21:04:48 by ysarac            #+#    #+#             */
/*   Updated: 2024/07/22 17:32:14 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

extern int	home_expend(t_main *shell, char **cmd, char *tmp, size_t i);

static int	dollar_expend(t_main *shell, char **cmd, char *tmp, size_t i)
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

static int	expand_value(t_command *cmds, t_main *shell)
{
	size_t	i;

	i = -1;
	shell->in_d = FALSE;
	shell->in_s = FALSE;
	while (cmds->value[++i])
	{
		if (ft_strnstr(cmds->value[i], "$", ft_strlen(cmds->value[i])))
		{
			if (!dollar_expend(shell, &cmds->value[i], NULL, 0))
				return (1);
		}
		if (ft_strnstr(cmds->value[i], "~", ft_strlen(cmds->value[i])))
		{
			if (!home_expend(shell, &cmds->value[i], NULL, 0))
				return (1);
		}
	}
	cmds->value = recreate_cmdval(cmds, 0, 0, 0);
	if (cmds->value == NULL)
		return (1);
	return (0);
}

static int	process_redirects(char **rdrs, t_main *shell, size_t *i)
{
	char	*tmp;

	if (ft_strnstr(rdrs[*i + 1], "$", ft_strlen(rdrs[*i + 1])))
	{
		if (!dollar_expend(shell, &rdrs[*i + 1], NULL, 0))
			return (1);
	}
	if (ft_strnstr(rdrs[*i + 1], "~", ft_strlen(rdrs[*i + 1])))
	{
		if (!home_expend(shell, &rdrs[*i + 1], NULL, 0))
			return (1);
	}
	if (!rdrs[*i + 1][0] || (ft_strnstr(rdrs[*i + 1], " ", ft_strlen(rdrs[*i
					+ 1])) && !(ft_strnstr(rdrs[*i + 1], "'", ft_strlen(rdrs[*i
						+ 1])) || ft_strnstr(rdrs[*i + 1], "\"",
					ft_strlen(rdrs[*i + 1])))))
	{
		return (-1);
	}
	tmp = remove_quotes(rdrs[*i + 1], FALSE, FALSE);
	if (!tmp)
		return (1);
	rdrs[*i + 1] = tmp;
	*i += 2;
	return (0);
}

static int	expand_rdr(t_command *cmds, t_main *shell)
{
	size_t	i;
	int		result;

	i = 0;
	shell->in_d = FALSE;
	shell->in_s = FALSE;
	while (cmds->rdrs && cmds->rdrs[i] && cmds->rdrs[i + 1])
	{
		result = process_redirects(cmds->rdrs, shell, &i);
		if (result == 1)
			return (1);
		if (result == -1)
		{
			cmds->in_work = 0;
			ft_putendl_fd("ft_sh: ambiguous redirect", 2);
			return (0);
		}
	}
	return (0);
}

void	expender(t_main *shell)
{
	t_command	*cmds;

	if (shell->control == 0)
		return ;
	cmds = shell->cmd;
	while (cmds)
	{
		if (expand_value(cmds, shell))
			return (shell->es = 12, exit_in_expander(shell));
		if (expand_rdr(cmds, shell))
			return (shell->es = 12, exit_in_expander(shell));
		cmds = cmds->next;
	}
}
