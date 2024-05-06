#ifndef FUNCTIONS_H
#define FUNCTIONS_H

# include "defines.h"
# include <sys/types.h>

//preparing
int 		initialize(t_main *shell, char **env);
void		start_shell(t_main *shell);

//lexer
void		lexer(t_main *shell);
t_tokens	*tlist(char **arr);
void		is_expendable(t_tokens *lst);
	//_tokens	*create_token(char	*arr);
	//int			token_add_back(t_tokens **list, t_tokens *new);

//free
void		free_env(t_main *shell);
void		free_double(char **arr);
void		free_tokens(t_tokens *tokens);

//utils
char		**get_cmd(char **env);
void		list_add_back(t_env **lst, t_env *tmp);
size_t		is_space(char *s);
t_env		*find_env(t_env *envs, char *wanted);
size_t		wordcount(char *s);
size_t		wordlen(const char *str);

#endif