/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarac <ysarac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:56:06 by ysarac            #+#    #+#             */
/*   Updated: 2024/07/03 17:57:30 by ysarac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

void	exit_cmd(t_command *cmds, t_main *shell)
{
	shell = (void *)shell;
	ft_putstr_fd("exit", cmds->fd[1]);
	ft_putstr_fd("\n", cmds->fd[1]);
	exit(0);
}

	/*
	free işlemleri yapılacak
	ama bu kısmı projenin sonuna bırakıyorum
	*/
