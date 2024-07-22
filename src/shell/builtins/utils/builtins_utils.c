/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 17:30:01 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/07/22 16:48:37 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"
#include "libft.h"
#include <stdlib.h>

extern int	execute_command(t_command *cmds, t_bool cmd_num, t_build *command,
				char *tmp);
extern int	handle_builtin_exit(t_bool cmd_num);

t_env	*sort_export(t_env *lst, int (*cmp)(int, int))
{
	char	*swap_name;
	char	*swap_value;
	t_env	*tmp;

	if (!lst || !lst->next)
		return (lst);
	tmp = lst;
	while (lst->next != NULL)
	{
		if (((*cmp)(lst->name[0], lst->next->name[0])) == 0)
		{
			swap_name = lst->name;
			swap_value = lst->value;
			lst->name = lst->next->name;
			lst->value = lst->next->value;
			lst->next->name = swap_name;
			lst->next->value = swap_value;
			lst = tmp;
		}
		else
			lst = lst->next;
	}
	lst = tmp;
	return (lst);
}

int	check_for_options(t_command *cmds)
{
	if (!cmds->value[1])
		return (1);
	if (cmds->value[1][0] == '-' && ft_strlen(cmds->value[1]) > 1)
	{
		ft_putendl_fd("ft_sh: no option required", cmds->fd[1]);
		return (0);
	}
	return (1);
}

int	ascending(int a, int b)
{
	return (a <= b);
}

int	check_argument(char *tmp, char *arg)
{
	if (!ft_strncmp(tmp, arg, ft_strlen(tmp)) && !ft_strncmp(tmp, arg,
			ft_strlen(arg)))
		return (1);
	return (0);
}

int	is_builtin(t_command *cmds, t_bool cmd_num, char *tmp, int i)
{
	static t_build	commands[] = {{"echo", echo}, {"cd", cd}, {"pwd", pwd},
	{"env", env}, {"unset", unset}, {"export", export}, {"exit",
		exit_cmd}, {NULL, NULL}};

	if (!tmp)
	{
		shell_keeper(NULL)->es = 12;
		exit_in_exec(shell_keeper(NULL));
		return (1);
	}
	while (commands[++i].name)
	{
		if (check_argument(tmp, commands[i].name))
		{
			return (execute_command(cmds, cmd_num, &commands[i], tmp));
		}
	}
	free(tmp);
	return (1);
}
