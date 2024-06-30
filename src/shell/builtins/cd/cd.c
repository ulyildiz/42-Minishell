
#include "functions.h"

void cd(t_command *cmds, t_main *shell)
{
    t_env *pwd;
    t_env *oldpwd;
    char *path;
	char *tmp;

    pwd = find_env(shell->envs, "PWD");
    oldpwd = find_env(shell->envs, "OLDPWD");
    if (!pwd)
    {
        pwd = (t_env *)malloc(sizeof(t_env));
        if (!pwd)
            return;
        pwd->name = ft_strdup("PWD");
        if (!pwd->name)
            return(free(pwd));
        pwd->value = getcwd(NULL, 0);
        if (!pwd->value)
            return(free(pwd),free(pwd->name));
        pwd->next = NULL;
        list_add_back(&shell->envs, pwd);
    }
    if (cmds->value[1] != NULL)
    {
        if (cmds->value[1][0] != '-')
        {
            path = ft_strjoin(pwd->value, "/");
            if (!path)
                return;
            tmp = ft_strappend(path, cmds->value[1], ft_strlen(cmds->value[1]));
            if (!tmp)
                return(free(path));
            path = tmp;
        }
        else if (cmds->value[1][0] == '-')
        {
            if (oldpwd)
                path = ft_strdup(oldpwd->value);
            else
                return (ft_putstr_fd("OLDPWD not set\n", cmds->fd[1]));
        }
    }
    else
    {
        if (find_env(shell->envs, "HOME") != NULL)
            path = ft_strdup(find_env(shell->envs, "HOME")->value);
        else
            return (ft_putstr_fd("HOME not set\n", cmds->fd[1]));
    }
    if (path && chdir(path) == 0)
    {
        if (!oldpwd)
        {
            oldpwd = (t_env *)malloc(sizeof(t_env));
            if (!oldpwd)
                return (free(path), perror("malloc failed"));
            oldpwd->name = ft_strdup("OLDPWD");
            if (!oldpwd->name)
                return(free(path),free(oldpwd));
            oldpwd->value = ft_strdup(pwd->value);
            if (!oldpwd->value)
                return(free(path), free(oldpwd), free(oldpwd->name));
            oldpwd->next = NULL;
            list_add_back(&shell->envs, oldpwd);
        }
        else
        {
            free(oldpwd->value);
            oldpwd->value = ft_strdup(pwd->value);
            if (!oldpwd->value)
                return (free(path), perror("ft_strdup failed"));
        }
        free(pwd->value);
        pwd->value = getcwd(NULL, 0);
        if (!pwd->value)
            return (free(path), perror("getcwd failed"));

        free(path);
    }
    else
    {
        perror("cd");
        if (path)
            free(path);
    }
    //d0nE
}

