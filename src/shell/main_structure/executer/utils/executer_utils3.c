/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 12:50:27 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/07/10 02:34:05 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "libft.h"

int	check_heredoc(t_command *cmd)
{
	int	i;
	int	k;

	k = 0;
	while (cmd)
	{
		i = -1;
		while (cmd->rdrs && cmd->rdrs[++i])
		{
			if (!ft_strncmp(cmd->rdrs[i], "<<", 2))
				k++;
		}
		cmd = cmd->next;
	}
	if (k == 0)
		return (0);
	return (1);
}
