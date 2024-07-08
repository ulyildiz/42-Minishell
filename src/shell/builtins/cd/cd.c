/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarac <ysarac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:56:16 by ysarac            #+#    #+#             */
/*   Updated: 2024/07/08 13:59:19 by ysarac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

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
		return (ft_putstr_fd("OLDPWD not set\n", cmds->fd[1]), shell->exit_status = 1, NULL);
}

static char *get_home_path(t_command *cmds, t_env *home)
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
		return (ft_putstr_fd("HOME not set\n", cmds->fd[1]), \
		shell->exit_status = 1, NULL);
}

static char	*get_cmd_path(t_command *cmds, t_env *pwd)
{
	char	*path;
	t_main	*shell;

	shell = shell_keeper(NULL);
	path = append_path(pwd->value, cmds->value[1]);
	if (!path)
	{
		ft_putstr_fd("Error generating path from command\n", cmds->fd[1]);
		shell->exit_status = 1;
		exit_for_fork(shell);
	}
	return (path);
}

static char	*get_path(t_command *cmds, t_env *pwd, t_env *oldpwd, t_env *home)
{
	char	*path;

	path = NULL;
	if (cmds->value[1] != NULL)
	{
		if (cmds->value[1][0] != '-')
			path = get_cmd_path(cmds, pwd);
		else if (cmds->value[1][0] == '-')
			path = get_oldpwd_path(cmds, oldpwd);
	}
	else
		path = get_home_path(cmds, home);
	return (path);
}

void	cd(t_command *cmds, t_main *shell)
{
	t_env	*pwd;
	t_env	*oldpwd;
	t_env	*home;
	char	*path;
	char	*gtcwd;

	gtcwd = getcwd(NULL, 0);
	pwd = update_or_create_env(&shell->envs, "PWD", gtcwd);
	oldpwd = find_env(shell->envs, "OLDPWD");
	home = find_env(shell->envs, "HOME");
	if (!pwd)
	{
		shell->exit_status = 1;
		return (free(gtcwd), exit_for_fork(shell));
	}
	path = get_path(cmds, pwd, oldpwd, home);
	if (!path)
		return (free(gtcwd));
	change_directory_and_update_envs(shell, path, pwd->value);
	free(gtcwd);
	free(path);
	if (update_env(shell) == -1)
		return (perror("update_env failed"));
}
