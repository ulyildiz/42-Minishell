/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarac <yunusemresarac@yaani.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:25:59 by ysarac            #+#    #+#             */
/*   Updated: 2024/07/08 16:25:59 by ysarac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

int	pwd(t_command *cmds, t_main *shell)
{
	char	*pwd;

	shell = (void *)shell;
	pwd = getcwd(NULL, 0);
	if (pwd != NULL)
		ft_putendl_fd(pwd, cmds->fd[1]);
	else
	{
		shell->exit_status = 1;
		ft_putendl_fd("pwd not set", cmds->fd[1]);
		return (0);
	}
	free(pwd);
	return (1);
}
