/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 06:20:44 by ysarac            #+#    #+#             */
/*   Updated: 2024/06/29 15:00:25 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

/********************************   Includes   ********************************/

# include "libft.h"
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>
# include <unistd.h>

/* ******************************    Defines     **************************** */

typedef int	t_bool;
# define TRUE	1
# define FALSE	0

/* ******************************   Enumaretes   ***************************  */
typedef enum e_token_types
{
	CMD,
	PIPE,
	RDR_IN,
	RDR_D_IN,
	RDR_OUT,
	HEREDOC
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
	R_P
}	t_is_pipe;

/* *******************************   Structs   ****************************** */

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
	int					pid;
	int					ifo; //is_file_opened
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
	char 		*tmp;
	int			exit_status;
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