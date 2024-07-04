/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: ysarac <ysarac@student.42.fr>              +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/07/03 17:57:51 by ysarac            #+#    #+#             */
/*   Updated: 2024/07/03 17:57:51 by ysarac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

void	pwd(t_command *cmds, t_main *shell)
{
	char	*pwd;

	shell = (void *)shell;
	pwd = getcwd(NULL, 0);
	if (pwd != NULL)
		ft_putendl_fd(pwd, cmds->fd[1]);
	else
		ft_putendl_fd("pwd not set", cmds->fd[1]);
	free(pwd);
}

	// d0nE