
#include "functions.h"

/*
** update_env yi  envye ekleme yaptığın yerde kullan.
*/

static t_env	*sort_export(t_env *lst, int (*cmp)(int, int))
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
void	export(t_command *cmds, t_main *shell)
{
	t_env	*export;
	t_env	*copy;
	t_env	*tmp;
	t_env	*env;
	int		i;
	char	**str;

	i = 1;
	while (cmds->value[i])
	{
		printf("cmds->value[i] = %s\n", cmds->value[i]);
		if (cmds->value[i][0] == '=')
		{
			ft_putstr_fd("invalid identifier\n",cmds->fd[1]);
			i++;
			continue;
		}
		str = ft_split(cmds->value[i], '=');
		if (str[0] && find_env(shell->envs, str[0]) != NULL)
		{
			if (str[1])
				find_env(shell->envs, str[0])->value = str[1];
		}
		else if (str[0] && find_env(shell->envs, str[0]) == NULL)
		{
			tmp = (t_env *)malloc(sizeof(t_env));
			if (!tmp)
				return ;
			tmp->name = str[0];
			tmp->value = "\0";
			tmp->next = NULL;
			if (str[1])
			{
				tmp->value = ft_strjoin("\"", str[1]);
				tmp->value = ft_strappend(tmp->value, "\"", 1);
			}
			list_add_back(&(shell->envs), tmp);
		}
		i++;
	}
		export = NULL;
    copy = shell->envs;
    while (copy) {
        tmp = (t_env *)malloc(sizeof(t_env));
        if (!tmp)
            return free_env(export);
        tmp->next = NULL;
        if (copy->name)
		{
            tmp->name = ft_strdup(copy->name);
            if (!tmp->name)
                return (free_env(export), free(tmp));
        }
        if (copy->value)
		{
            tmp->value = ft_strdup(copy->value);
            if (!tmp->value)
                return (free(tmp->name),free(tmp), free_env(export));
        }
        list_add_back(&export, tmp);
        copy = copy->next;
    }
	export = sort_export(export, ascending);
	env = export;
	while (env && cmds->value[1] == NULL)
	{
		ft_putstr_fd("declare -x ", cmds->fd[1]);
		ft_putstr_fd(env->name, cmds->fd[1]);
		if (env->value != NULL && env->value[0] != '\0')
		{
			ft_putstr_fd("=", cmds->fd[1]);
			ft_putstr_fd("\"",cmds->fd[1]);
			ft_putstr_fd(env->value, cmds->fd[1]);
			ft_putstr_fd("\"",cmds->fd[1]);
		}
		ft_putstr_fd("\n", cmds->fd[1]);
		env = env->next;
	}
	free_env(export);
	//probably d0nE
}
