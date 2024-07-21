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
#include "libft.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

extern t_env *update_or_create_env(t_env **envs, char *name, char *value);
extern  void change_directory_and_update_envs(t_main *shell, char *path,
				char *old_pwd_value, char *gtcwd);

static char *get_oldpwd_path(t_command *cmds, t_env *oldpwd)
{
	char *path;
	t_main *shell;

	shell = shell_keeper(NULL);
	if (oldpwd)
	{
		path = ft_strdup(oldpwd->value);
		if (!path)
		{
			ft_putstr_fd("Error duplicating OLDPWD value\n", cmds->fd[1]);
			shell->es = 1;
			exit_for_fork(shell);
		}
		ft_putendl_fd(path, cmds->fd[1]);
		return (path);
	} 
	else 
	{
		ft_putstr_fd("OLDPWD not set\n", cmds->fd[1]);
		shell->es = 1;
		return (ft_calloc(sizeof(char), 1));
	}
}

static char *get_home_path(t_command *cmds, t_env *home)
{
	char *path;
	t_main *shell;

	shell = shell_keeper(NULL);
	if (home)
	{
		path = ft_strdup(home->value);
		if (!path)
		{
			ft_putstr_fd("Error duplicating HOME value\n", cmds->fd[1]);
			shell->es = 1;
			exit_for_fork(shell);
		}
		return (path);
	}
	else
	{
		ft_putstr_fd("HOME not set\n", cmds->fd[1]);
		shell->es = 1;
		return (ft_calloc(sizeof(char), 1));
	}
}

static char *get_path(t_command *cmds, t_env *oldpwd, t_env *home)
{
	if (cmds->value[1] != NULL) 
	{
		if (cmds->value[1][0] != '-')
			return (ft_strdup(cmds->value[1]));
		else
			return (get_oldpwd_path(cmds, oldpwd));
	}
	else
		return (get_home_path(cmds, home));
}

int cd(t_command *cmds, t_main *shell)
{
	t_env *pwd;
 	t_env *oldpwd;
	t_env *home;
	char *path;
	char *gtcwd;

	if (!check_for_options(cmds))
		return (1);
	gtcwd = getcwd(NULL, 0);
	if (!gtcwd)
		return (perror("getcwd failed"), shell->es = 1, 0);
	pwd = update_or_create_env(&shell->envs, "PWD", gtcwd);
	oldpwd = find_env(shell->envs, "OLDPWD");
	home = find_env(shell->envs, "HOME");
	if (!pwd)
	{
		shell->es = 1;
		free(gtcwd);
		exit_for_fork(shell);
	}
	path = get_path(cmds, oldpwd, home);
	if (!path)
		return (free(gtcwd), 0);
	change_directory_and_update_envs(shell, path, pwd->value, NULL);
	if (update_env(shell) == 0)
		return (perror("update_env failed"), free(gtcwd), free(path),0);
	return (free(gtcwd), free(path), 1);
}
