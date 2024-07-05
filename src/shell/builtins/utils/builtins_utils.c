/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarac <ysarac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 17:30:01 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/07/04 07:09:29 by ysarac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

t_env	*sort_export(t_env *lst, int (*cmp)(int, int))
{
	char	*swap_name;
	char	*swap_value;
	t_env	*tmp;

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

int	ascending(int a, int b)
{
	return (a <= b);
}

int	is_builtin(t_command *cmds, t_main *shell, t_bool cmd_num)
{
	int				i;
	static t_build	commands[] = {{"echo", echo}, {"cd", cd}, {"pwd", pwd},
	{"env", env}, {"unset", unset}, {"export", export}, {"exit",
		exit_cmd}, {NULL, NULL}};

	i = 0;
	while (commands[i].name)
	{
		if (!ft_strncmp(ft_strlower(cmds->value[0]), commands[i].name,
				ft_strlen(cmds->value[0]))
			&& !ft_strncmp(ft_strlower(cmds->value[0]), commands[i].name,
				ft_strlen(commands[i].name)))
		{
			commands[i].func(cmds, shell);
			if (cmd_num)
				exit_for_fork(shell);
			else
				return (0);
		}
		i++;
	}
	return (1);
}
