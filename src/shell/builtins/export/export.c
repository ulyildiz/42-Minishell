#include "functions.h"

static void add_new_env(t_env **envs, char **str)
{
	t_env	*tmp;

	tmp = (t_env *)malloc(sizeof(t_env));
    if (!tmp)
		return;
    tmp->name = str[0];
	tmp->value = "\0";
	if (str[1])
		tmp->value = ft_strjoin(tmp->value, str[1]);
    tmp->next = NULL;
    list_add_back(envs, tmp);
}

static void process_commands(t_command *cmds, t_main *shell)
{
	char	**str;
	int		i;
	t_env	*env_var;

	i = 1;
    while (cmds->value[i])
	{
        if (cmds->value[i][0] == '=')
		{
            ft_putstr_fd("invalid identifier\n", cmds->fd[1]);
            i++;
            continue;
        }
        str = ft_split(cmds->value[i], '=');
        env_var = find_env(shell->envs, str[0]);
        if (str[0] && env_var != NULL)
		{
            if (str[1])
                env_var->value = str[1];
        }
		else if (str[0] && env_var == NULL)
            add_new_env(&(shell->envs), str);
        i++;
    }
}

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

static void print_export(t_env *env, int fd)
{
    while (env)
	{
        ft_putstr_fd("declare -x ", fd);
        ft_putstr_fd(env->name, fd);
        if (env->value != NULL && env->value[0] != '\0')
		{
            ft_putstr_fd("=", fd);
            ft_putstr_fd("\"", fd);
            ft_putstr_fd(env->value, fd);
            ft_putstr_fd("\"", fd);
        }
        ft_putstr_fd("\n", fd);
        env = env->next;
    }
}

void export(t_command *cmds, t_main *shell)
{
	t_env	*export;

	export = NULL;
    process_commands(cmds, shell);
    if (update_env(shell) == 0)
        return;
    copy_env(&export, shell->envs);
	export = sort_export(export, ascending);
    if (cmds->value[1] == NULL)
        print_export(export, cmds->fd[1]);
    update_env(shell);
    free_env(export);
}
