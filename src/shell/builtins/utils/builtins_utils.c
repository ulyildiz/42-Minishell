/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarac <yunusemresarac@yaani.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 17:30:01 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/07/08 18:21:23 by ysarac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

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

int	ascending(int a, int b)
{
	return (a <= b);
}

int	is_builtin(t_command *cmds, t_main *shell, t_bool cmd_num)
{
	int				i;
	char			*tmp;
	static t_build	commands[] = {{"echo", echo}, {"cd", cd}, {"pwd", pwd},
			{"env", env}, {"unset", unset}, {"export", export}, {"exit",
			exit_cmd}, {NULL, NULL}};

	i = 0;
	tmp = ft_strlower(ft_strdup(cmds->value[0]));
	if (!tmp)
		return (1);
	while (commands[i].name)
	{
		if (!ft_strncmp(tmp, commands[i].name, ft_strlen(tmp))
			&& !ft_strncmp(tmp, commands[i].name, ft_strlen(commands[i].name)))
		{
			free(tmp);
			if (!commands[i].func(cmds, shell))
			{
				if (cmd_num)
					exit_for_fork(shell);
				else
					exit_in_exec(shell);
			}
			if (cmd_num)
				exit_for_fork(shell);
			else
				return (0);
		}
		i++;
	}
	return (free(tmp), 1);
}
