/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:56:16 by ysarac            #+#    #+#             */
/*   Updated: 2024/07/10 02:36:58 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"
#include <unistd.h>
#include <stdio.h>
#include "libft.h"

extern t_env	*update_or_create_env(t_env **envs, char *name, char *value);

static char	*get_oldpwd_path(t_command *cmds, t_env *oldpwd)
{
	char	*path;
	t_main	*shell;

	shell = shell_keeper(NULL);
	if (oldpwd)
	{
		path = ft_strdup(oldpwd->value);
		if (!path)
		{
			ft_putstr_fd("Error duplicating OLDPWD value\n", cmds->fd[1]);
			shell->exit_status = 1;
			exit_for_fork(shell);
		}
		return (ft_putendl_fd(path, cmds->fd[1]), path);
	}
	else
		return (ft_putstr_fd("OLDPWD not set\n", cmds->fd[1]),
			shell->exit_status = 1, NULL);
}

static char	*get_home_path(t_command *cmds, t_env *home)
{
	char	*path;
	t_main	*shell;

	shell = shell_keeper(NULL);
	if (home)
	{
		path = ft_strdup(home->value);
		if (!path)
		{
			ft_putstr_fd("Error duplicating HOME value\n", cmds->fd[1]);
			shell->exit_status = 1;
			exit_for_fork(shell);
		}
		return (path);
	}
	else
		return (ft_putstr_fd("HOME not set\n", cmds->fd[1]),
			shell->exit_status = 1, NULL);
}

static char	*get_path(t_command *cmds, t_env *oldpwd, t_env *home)
{
	char	*path;

	path = NULL;
	if (cmds->value[1] != NULL)
	{
		if (cmds->value[1][0] != '-')
			path = ft_strdup(cmds->value[1]);
		else if (cmds->value[1][0] == '-')
			path = get_oldpwd_path(cmds, oldpwd);
	}
	else
		path = get_home_path(cmds, home);
	return (path);
}

int	cd(t_command *cmds, t_main *shell)
{
	t_env	*pwd;
	t_env	*oldpwd;
	t_env	*home;
	char	*path;
	char	*gtcwd;

	if (!check_for_options(cmds))
		return (1);
	gtcwd = ft_strdup(cmds->value[1]);
	pwd = update_or_create_env(&shell->envs, "PWD", gtcwd);
	oldpwd = find_env(shell->envs, "OLDPWD");
	home = find_env(shell->envs, "HOME");
	if (!pwd)
	{
		shell->exit_status = 1;
		return (free(gtcwd), exit_for_fork(shell), 0);
	}
	path = get_path(cmds, oldpwd, home);
	if (!path)
		return (free(gtcwd), 0);
	change_directory_and_update_envs(shell, path, pwd->value);
	if (update_env(shell) == -1)
		return (free(gtcwd), free(path), perror("update_env failed"), 0);
	return (free(gtcwd), free(path), 1);
}
