/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:48:13 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/07/19 18:48:13 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"
#include "libft.h"

static void take_len(const char *str, size_t *i, t_bool in_s, t_bool  in_d)
{
    while (str[*i] && (!is_whitespace(str[*i]) || in_s || in_d))
    {
        toggle_quote(str[*i], &in_s, &in_d);
        if ((str[*i] == '\'' && !in_d) || (str[*i] == '"' && !in_s))
        {
            (*i)++;
            continue;
        }
        (*i)++;
    }
}

static void copy_characters(const char *src, char *dest, size_t start, size_t end)
{
    size_t	tmp_idx;
    size_t	k;
	t_bool	in_s;
	t_bool	in_d;

	in_s = FALSE;
    in_d = FALSE;
	tmp_idx = 0;
	k = start;
    while (k < end)
    {
        toggle_quote(src[k], &in_s, &in_d);
        if ((src[k] == '\'' && !in_d) || (src[k] == '"' && !in_s))
        {
            k++;
            continue;
        }
        dest[tmp_idx++] = src[k];
        k++;
    }
}

char *createword(t_command *cmd, size_t j, size_t *i)
{
    size_t	start;
	size_t	len;
    char	*tmp;

	start = *i;
    take_len(cmd->value[j], i, FALSE, FALSE);
    len = *i - start;
    tmp = ft_calloc(len + 1, sizeof(char));
	if (!tmp)
        return (NULL);
    copy_characters(cmd->value[j], tmp, start, *i);
    return (tmp);
}