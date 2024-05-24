/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:33:54 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/05/23 11:33:54 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"
#include "42-libft/libft.h"
#include <stdio.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>

static void official_executer(t_command *cmds, t_main *shell, int i)
{
	cmds->pid = fork();
	if (cmds->pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (cmds->pid == 0)
	{
		close(cmds->pipefd[i % 2]);
		dup2(cmds->pipefd [ ( i % 2 ) ^ 1 ] , STDOUT_FILENO );
		close(cmds->pipefd[ ( i % 2 ) ^ 1 ] );
		execve(cmds->cmd_and_path, cmds->value, shell->env_for_execve_function); // Execute ls -la
        perror("exec ls");
        exit(EXIT_FAILURE);
	}
	
	

}


int	executor(t_main *shell)
{
	int i;
	i = 0;
	t_command *tmp = shell->cmd;
	t_command *cmds;

	cmds = shell->cmd;
	while(cmds)
	{
		if (pipe(cmds->pipefd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		if (is_builtin(cmds, shell))
			;
		else if (accessibility(cmds,shell))
			official_executer(cmds, shell, i);
		else
			return (ft_putstr_fd("ft_sh: command not found: ", 2),
				ft_putstr_fd(cmds->value[0], 2), ft_putchar_fd('\n', 2), 2);
		i++;
		cmds = cmds->next;
	}
	return (1);
}