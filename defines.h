#ifndef DEFINES_H
#define DEFINES_H

typedef enum	e_token_types
{
	CMD, // komut kısım
	CTRL, // kontrol tokenleri
	PIPE, // pipe
	RDR, // redirection tokenleri
	D_QUOTE,//çift tırnak içerisinde expand olucak
	QUOTE // tek tırnak içerisinde expand olmayacak
}	t_token_types;

typedef enum	e_quote_value
{
	NONE,
	WITHIN_D_Q,
	WITHIN_Q
}	t_quote_value;

typedef struct	s_tokens
{
	t_token_types	type;
	t_quote_value	is_quoted;
	char			*value;
	struct s_tokens	*next;
}	t_tokens;

typedef struct	s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_main
{
	t_env		*envs; //envler için
	t_tokens	*token;
    char		**paths; // komutlar için parçalanmış pathler
	char		*prompt;
	char		*cmd_line; // komut satırından okunan satır
}   t_main;

#endif