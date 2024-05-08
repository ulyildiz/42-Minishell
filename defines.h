#ifndef DEFINES_H
#define DEFINES_H

typedef enum	e_token_types
{
	CMD, // komut kısım
	CTRL, // kontrol tokenleri
	PIPE, // pipe
	RDR, // redirection tokenleri
	D_QUOTE,//çift tırnak 
	QUOTE // tek tırnak
}	t_token_types;

typedef enum	e_is_expendable
{
	NONE,
	WITHIN_D_Q,
	WITHIN_Q,
	NONE_TILDE
}	t_is_expendable;

typedef struct	s_tokens
{
	t_token_types	type;
	t_is_expendable	is_expend;
	char			*value;
	struct s_tokens	*next;
}	t_tokens;

typedef struct s_command
{
	char				*value;
	struct s_command	*prev;
	struct s_command	*next;
}	t_command;

typedef struct	s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_main
{
	t_env		*envs; //envler için
	t_tokens	*token; //token listesi (whitespacelere ve tokenlere göre splitli
//	t_command	*cmd;
	char		**paths; // komutlar için parçalanmış pathler
	char		*prompt;
	char		*cmd_line; // komut satırından okunan satır
}   t_main;

#endif