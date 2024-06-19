/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:55:47 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/06/11 14:55:47 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define TRUE 1
# define FALSE 0

typedef int	t_bool;

typedef enum e_token_types
{
	CMD,
	PIPE,
	RDR_IN,
	RDR_D_IN,
	RDR_OUT,
	HEREDOC,
	D_QUOTE,
	QUOTE
}				t_token_types;

typedef enum e_is_expendable
{
	NONE,
	WITHIN_D_Q,
	WITHIN_Q,
	NONE_TILDE
}	t_is_expendable;

typedef enum e_is_pipe
{
	NONE_P,
	L_P,
	R_P,
	B_P
}	t_is_pipe;

typedef enum e_is_rdr
{
	NONE_RDR,
	R_RDR_IN,
	R_D_RDR_IN,
	R_RDR_OUT,
	R_RDR_H,
	L_RDR_IN,
	L_D_RDR_IN,
	L_RDR_OUT,
	L_RDR_H
}	t_is_rdr;

typedef struct s_tokens
{
	t_token_types	type;
	t_is_expendable	is_expend;
	char			*value;
	struct s_tokens	*next;
}	t_tokens;

typedef struct s_command
{
	char				**value;
	char				**rdrs;
	char				*cmd_and_path;
	int					fd[2];
	t_is_pipe			where_p;
	t_is_rdr			where_r;
	int					pid;
	struct s_command	*prev;
	struct s_command	*next;
}	t_command;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_main
{
	t_env		*envs;
	t_tokens	*token;
	t_command	*cmd;
	t_bool		in_s;
	t_bool		in_d;
	int			control;
	char		**paths;
	char		*prompt;
	char		**env_for_execve_function;
	char		*cmd_line;
}	t_main;

typedef struct s_build
{
	char	*name;
	void	(*func)(t_command *cmds, t_main *shell);
}	t_build;

#endif
