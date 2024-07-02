#include "functions.h"


char *get_oldpwd_path(t_command *cmds, t_env *oldpwd)
{
	char *path;

    if (oldpwd)
	{
        path = ft_strdup(oldpwd->value);
        if (!path)
            ft_putstr_fd("Error duplicating OLDPWD value\n", cmds->fd[1]);
        return (ft_putendl_fd(path, cmds->fd[1]),path);
    }
	else
        return (ft_putstr_fd("OLDPWD not set\n", cmds->fd[1]), NULL);
}

char *get_home_path(t_command *cmds, t_env *home)
{
	char *path;

    if (home) 
	{
        path = ft_strdup(home->value);
        if (!path)
            ft_putstr_fd("Error duplicating HOME value\n", cmds->fd[1]);
        return (path);
    }
	else
        return (ft_putstr_fd("HOME not set\n", cmds->fd[1]),NULL);
}

char	*get_cmd_path(t_command *cmds, t_env *pwd)
{
    char	*path;

	path  = append_path(pwd->value, cmds->value[1]);
    if (!path) 
        ft_putstr_fd("Error generating path from command\n", cmds->fd[1]);
    return (path);
}

char *get_path(t_command *cmds, t_env *pwd, t_env *oldpwd, t_env *home)
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

void cd(t_command *cmds, t_main *shell)
{
    t_env *pwd;
    t_env *oldpwd;
    t_env *home;
	char *path;

	pwd = update_or_create_env(&shell->envs, "PWD", getcwd(NULL, 0));
	oldpwd = find_env(shell->envs, "OLDPWD");
	home = find_env(shell->envs, "HOME");
    if (!pwd)
		return;
    path = get_path(cmds, pwd, oldpwd, home);
    if (!path)
		return;
    if (chdir(path) == 0)
	{
        if (!update_or_create_env(&shell->envs, "OLDPWD", pwd->value))
            return (free(path),perror("update_or_create_env failed"));
        if (!update_or_create_env(&shell->envs, "PWD", getcwd(NULL, 0))) 
            return (free(path),perror("update_or_create_env failed"));
    }
	else
        perror("cd");
    free(path);
}
