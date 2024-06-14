/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarac <ysarac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 06:33:08 by ysarac            #+#    #+#             */
/*   Updated: 2024/06/14 07:35:30 by ysarac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

int	main(int ac, char** av, char **env)
{
	t_main	shell;

	//signal_reciever();
	av = (void *)av;
	if (ac >=2)
		return(ft_putstr_fd("Too much argument.", 2), 1);
	if (!initialize(&shell, env))
		return (perror("Initialize"), 1);
	start_shell(&shell);
    return (0);
}