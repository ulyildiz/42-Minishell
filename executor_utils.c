/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:07:33 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/06/11 15:08:32 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42-libft/libft.h"
#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	accessibility(t_command *cmds, t_main *shell)
{
	size_t	i;
	char	*tmp;

	i = 0;
	if (access(cmds->value[0], X_OK) != 0)
	{
		tmp = ft_strjoin("/", cmds->value[0]);
		if (!tmp)
			return (perror("Access"), 0);
		while (shell->paths[i])
		{
			cmds->cmd_and_path = ft_strjoin(shell->paths[i], tmp);
			if (access(cmds->cmd_and_path, X_OK) == 0)
				return (free(tmp), 1);
			free(cmds->cmd_and_path);
			i++;
		}
		free(tmp);
	}
	else
	{
		cmds->cmd_and_path = ft_strdup(cmds->value[0]);
		return (1);
	}
	return (0);
}

void	close_fd(t_command *cmds, int flag)
{
	if (!cmds)
		return ;
}

void	echo(t_command *cmds, t_main *shell)
{
	printf("echo command\n");
}

void	cd(t_command *cmds, t_main *shell)
{
	/* şunu farkettim bash kabuğunu ilk çağırdığımda envde old pwd yoktu
	cd ile yer değiştirdikten sonra old pwd set oldu
	bu durumu da kontrol etmeliyim
	ona göre old pwd yi set etmeliyim
	*/
	t_env *pwd;
	t_env *old_pwd;
	char *cd_path;

	pwd = find_env(shell->envs, "PWD");        // kontrol et not set olabilir
	old_pwd = find_env(shell->envs, "OLDPWD"); // kontrol et not set olabilir
	if (cmds->value[1] != NULL)
	{
		if (cmds->value[1][0] != '-')
		{
			cd_path = ft_strjoin(pwd->value, "/");
			cd_path = ft_strappend(cd_path, cmds->value[1],
					ft_strlen(cmds->value[1]));
		}
		else if (cmds->value[1][0] == '-')
		{
			cd_path = find_env(shell->envs, "OLDPWD")->value;
			ft_putstr_fd(cd_path, cmds->fd[1]);
			ft_putstr_fd("\n", cmds->fd[1]);
		}
	}
	else
		cd_path = find_env(shell->envs, "HOME")->value;

	if (chdir(cd_path) == 0)
	{
		//free(old_pwd->value);
		old_pwd->value = pwd->value;
		//free(pwd->value);
		pwd->value = getcwd(NULL, 0);
	}
	else
		perror("cd");
	//free(cd_path);
	//belki "-" durumunda home a kadar sa ~ bastırabiliriz pipe a
	//freelere bakılacak
	//aklıma gelen bütün ihtimalleri denedim sıkıntı yok şuan freeleri kontrol ettikten sonra tekrar denemeliyim
}

void	pwd(t_command *cmds, t_main *shell)
{
	t_env *pwd;

	pwd = find_env(shell->envs, "PWD");
	if (pwd != NULL)
	{
		ft_putstr_fd(pwd->value, cmds->fd[1]);
		ft_putstr_fd("\n", cmds->fd[1]);
		//normal bash ile karşılaştırdım newline atıyor rdr de bile
	} // olmama durumunu kontrol etmelisin
}

void	env(t_command *cmds, t_main *shell)
{
	t_env *env;

	env = shell->envs;
	while (env != NULL)
	{
		if (env->name != 0)
		{
			ft_putstr_fd(env->name, cmds->fd[1]);
			ft_putstr_fd("=", cmds->fd[1]);
		}
		if (env->value != NULL)
			ft_putstr_fd(env->value, cmds->fd[1]);
		ft_putstr_fd("\n", cmds->fd[1]);
		// eğer value ya sahip olmayan nameler varsa = den sonra direkt newline atmıyordu ondan if dışında
		env = env->next;
	}
}

void	unset(t_command *cmds, t_main *shell)
{
	printf("unset command\n");
}

void	export(t_command *cmds, t_main *shell)
{
	return ;
}

void	exit_cmd(t_command *cmds, t_main *shell)
{
	ft_putstr_fd("exit", cmds->fd[1]);
	ft_putstr_fd("\n", cmds->fd[1]);
	/*
	free işlemleri yapılacak
	ama bu kısmı projenin sonuna bırakıyorum
	*/
	exit(0);
}

int	is_builtin(t_command *cmds, t_main *shell)
{
	int i;
	static t_build commands[] = {
		{"echo", echo},
		{"cd", cd},
		{"pwd", pwd},
		{"env", env},
		{"unset", unset},
		{"export", export},
		{"exit", exit_cmd},
		{NULL, NULL}};

	i = 0;
	while (commands[i].name)
	{
		if (ft_strncmp(cmds->value[0], commands[i].name,
				ft_strlen(cmds->value[0])) == 0)
		{
			commands[i].func(cmds, shell);
			return (1);
		}
		i++;
	}
	return (0);
}
