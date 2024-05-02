#ifndef FUNCTIONS_H
#define FUNCTIONS_H

# include "defines.h"
# include <sys/types.h>

//init
int 	initialize(t_main *shell, char **env);

//shell
void		start_shell(t_main *shell);

//utils
char		**get_cmd(char **env);
void		list_add_back(t_env **lst, t_env *tmp);
size_t		is_space(char *s);
t_env		*find_env(t_env *envs, char *wanted);
size_t		wordcount(char *s);

//lexer
void		lexer(t_main *shell);
t_tokens	*create_token(char	*arr);
void		token_add_back(t_tokens *list, t_tokens *new);

//free
void		free_env(t_main *shell);
void		free_double(char **arr);

#endif