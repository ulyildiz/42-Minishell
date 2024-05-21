#ifndef DEFINES_H
#define DEFINES_H

typedef enum	e_token_types
{
	CMD, // komut kısım
	PIPE, // pipe
	RDR_IN, // redirection tokenleri
	RDR_OUT,
	HEREDOC,
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


typedef enum	e_is_pipe
{
	NONE_P,
	L_P,
	R_P,
	B_P
}	t_is_pipe;

typedef enum	e_is_rdr
{
	NONE_RDR,
	R_RDR_IN,
	R_RDR_OUT,
	R_RDR_H,
	L_RDR_IN,
	L_RDR_OUT,
	L_RDR_H
}	t_is_rdr;

typedef struct	s_tokens
{
	t_token_types	type;
	t_is_expendable	is_expend;
	char			*value;
	struct s_tokens	*next;
}	t_tokens;

typedef struct s_command
{

	char				**value;
	int					infile;
	int					outfile;
	t_is_pipe			where_p;
	t_is_rdr			where_r;
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
	t_command	*cmd;
	int			control;
	char		**paths; // komutlar için parçalanmış pathler
	char		*prompt;
	char		*cmd_line; // komut satırından okunan satır
}   t_main;

#endif