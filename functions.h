#ifndef FUNCTIONS_H
#define FUNCTIONS_H

# include "defines.h"

//init
int 	initialize(t_main *shell, char **env);

//shell
void	start_shell(t_main *shell);

//utils
char	**get_cmd(char **env);
void	list_add_back(t_env **lst, t_env *tmp);
int		is_space(char *s);
t_env	*find_env(t_env *envs, char *wanted);

//free
void	free_env(t_main *shell);

#endif