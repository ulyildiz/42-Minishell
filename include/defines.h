/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarac <ysarac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 07:12:34 by ysarac            #+#    #+#             */
/*   Updated: 2024/07/04 07:12:34 by ysarac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

/********************************   Includes   ********************************/
/* ******************************   Defines      **************************** */

typedef int	t_bool;
# define TRUE 1
# define FALSE 0

/* ******************************   Enumaretes   ***************************  */
typedef enum e_token_types
{
	CMD,
	PIPE,
	RDR_IN,
	RDR_D_IN,
	RDR_OUT,
	HEREDOC
}	t_token_types;

typedef enum e_is_pipe
{
	NONE_P,
	L_P,
	R_P
}	t_is_pipe;

/* *******************************   Structs   ****************************** */

typedef struct s_tokens
{
	t_token_types		type;
	char				*value;
	struct s_tokens		*next;
}	t_tokens;

typedef struct s_command
{
	int					in_work;
	char				**value;
	char				**rdrs;
	char				*cmd_and_path;
	int					fd[2];
	int					here_fd;
	t_is_pipe			where_p;
	int					pid;
	struct s_command	*prev;
	struct s_command	*next;
}	t_command;

typedef struct s_env
{
	char				*name;
	char				*value;
	struct s_env		*next;
}	t_env;

typedef struct s_main
{
	t_env				*envs;
	t_tokens			*token;
	t_command			*cmd;
	t_bool				in_s;
	t_bool				in_d;
	char				*tmp;
	int					es;
	int					control;
	char				**paths;
	char				*prompt;
	char				**env_for_execve_function;
	char				*cmd_line;
}	t_main;

typedef struct s_build
{
	char				*name;
	int					(*func)(t_command *cmds, t_main *shell);
}	t_build;

#endif