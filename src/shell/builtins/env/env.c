
#include "functions.h"

void    env(t_command *cmds, t_main *shell) {
    t_env   *export;
    t_env   *copy;
    t_env   *tmp;
	int		i;
	char	**str;
	t_env	*env;

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
	i = 1;
	while (cmds->value[i])
	{
		str = ft_split(cmds->value[i], '=');
		if (str[0] && find_env(export, str[0]) != NULL)
		{
			if (str[1])
				find_env(export, str[0])->value = str[1];
		}
		else if (str[0] && find_env(export, str[0]) == NULL)
		{
			tmp = (t_env *)malloc(sizeof(t_env));
			if (!tmp)
				return ;
			tmp->name = str[0];
			tmp->value = "\0";
			tmp->next = NULL;
			if (str[1])
			{
				tmp->value = ft_strdup(str[1]);
			}
			list_add_back(&(export), tmp);
		}
		i++;
	}
	env = export;
	while (env)
	{
		ft_putstr_fd(env->name, cmds->fd[1]);
		if (env->value && env->value[0] != '\0')
		{
			ft_putstr_fd("=", cmds->fd[1]);
			ft_putstr_fd(env->value, cmds->fd[1]);
		}
		ft_putstr_fd("\n", cmds->fd[1]);
		// eğer value ya sahip olmayan nameler varsa = den sonra direkt newline atmıyordu ondan if dışında
		env = env->next;
	}
	free_env(export);
	//probably d0nE
}
