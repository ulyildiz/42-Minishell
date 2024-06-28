
#include "functions.h"

void	env(t_command *cmds, t_main *shell)
{
	t_env	*env;

	env = shell->envs;
	while (env != NULL)
	{
		if (env->name != NULL)
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