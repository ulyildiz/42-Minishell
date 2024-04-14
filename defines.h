#ifndef DEFINES_H
#define DEFINES_H


typedef struct	s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_main
{
	t_env	*envs; // prompt ve env builtini için
    char    **paths; // komutlar için parçalanmış pathler
	char	*prompt;
	char	*cmd_line; // komut satırından okunan satır
}   t_main;

#endif