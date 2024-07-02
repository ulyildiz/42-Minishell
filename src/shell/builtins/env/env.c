#include "functions.h"

static void copy_env(t_env **export, t_env *src)
{
	t_env	*tmp;

    while (src)
	{
        tmp = (t_env *)malloc(sizeof(t_env));
        if (!tmp)
            return(free_env(*export));
        tmp->next = NULL;
        if (src->name)
		{
            tmp->name = ft_strdup(src->name);
            if (!tmp->name) 
                return(free(tmp),free_env(*export));
        } 
        if (src->value)
		{
            tmp->value = ft_strdup(src->value);
            if (!tmp->value)
                return(free(tmp->name),free(tmp),free_env(*export));
        } 
		else
            tmp->value = "\0";
        list_add_back(export, tmp);
        src = src->next;
    }
}

void update_or_add_env(t_env **export, char *str)
{
	t_env	*tmp;
	char	**split;

	split = ft_split(str, '=');
    if (split[0] && find_env(*export, split[0]) != NULL)
	{
        if (split[1])
            find_env(*export, split[0])->value = split[1];
    } 
	else if (split[0] && find_env(*export, split[0]) == NULL)
	{
        tmp = (t_env *)malloc(sizeof(t_env));
        if (!tmp)
			return;
        tmp->name = split[0];
		tmp->value = "\0";
		if (split[1])
			tmp->value = ft_strdup(split[1]);
        tmp->next = NULL;
        list_add_back(export, tmp);
    }
}

void print_env(t_env *env, int fd)
{
    while (env)
	{
        ft_putstr_fd(env->name, fd);
        if (env->value && env->value[0] != '\0')
		{
            ft_putstr_fd("=", fd);
            ft_putstr_fd(env->value, fd);
        }
        ft_putstr_fd("\n", fd);
        env = env->next;
    }
}

void env(t_command *cmds, t_main *shell)
{
	t_env	*export;
	int		i;

	i = 1;
	export = NULL;
    copy_env(&export, shell->envs);
    while (cmds->value[i]) 
        update_or_add_env(&export, cmds->value[i++]);
    print_env(export, cmds->fd[1]);
    free_env(export);
}
//d0nE