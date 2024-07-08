/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarac <ysarac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 21:04:48 by ysarac            #+#    #+#             */
/*   Updated: 2024/07/07 22:22:30 by ysarac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

static int	dollar_expend(t_main *shell, t_tokens *token, char	*tmp, size_t i)
{
	size_t	start;

	tmp = ft_strdup("");
	while (token->value[i])
	{
		if (token->value[i] == '$' && !shell->in_s)
			tmp = handle_dollar_sign(tmp, token->value, &i, shell);
		else
		{
			start = i;
			while (token->value[i] && !(token->value[i] == '$' && !shell->in_s))
			{
				toggle_quote(token->value[i], &shell->in_s, &shell->in_d);
				i++;
			}
			tmp = append_literal(tmp, token->value, &start, &i);
		}
		if (!tmp)
			return (perror("Dollar Expend"), 0);
	}
	return (free(token->value), token->value = tmp, 1);
}

static int	home_expend(t_main *shell, t_tokens *token, char *tmp, size_t i)
{
	tmp = ft_strdup("");
	while (token->value[i] && tmp)
	{
		if (token->value[i] == '~' && !shell->in_s && !shell->in_d)
		{
			if ((i > 0 && !is_whitespace(token->value[i - 1])) || \
			(!is_whitespace(token->value[i + 1]) && token->value[i + 1] != '\0'
					&& token->value[i + 1] != '/'))
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
			tmp = ft_strappend(tmp, &token->value[i], 1);
		toggle_quote(token->value[i], &shell->in_s, &shell->in_d);
		i++;
	}
	if (!tmp)
		return (perror("Home expand"), 0);
	return (token->value = tmp, 1);
}

void	expender(t_main *shell)
{
	t_tokens	*t;
	char		*tmp;

	if (shell->control == 0)
		return ;
	tmp = NULL;
	t = shell->token;
	while (t)
	{
		shell->in_d = FALSE;
		shell->in_s = FALSE;
		if (ft_strnstr(t->value, "$", ft_strlen(t->value)))
		{
			if (!dollar_expend(shell, t, tmp, 0))
				return (exit_in_lex_ex(shell));
		}
		if (ft_strnstr(t->value, "~", ft_strlen(t->value)))
		{
			if (!home_expend(shell, t, NULL, 0))
				return (exit_in_lex_ex(shell));
		}
		t = t->next;
	}
}
