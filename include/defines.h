/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarac <ysarac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 06:20:44 by ysarac            #+#    #+#             */
/*   Updated: 2024/06/14 11:02:51 by ysarac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
#define DEFINES_H

/********************************   Defines   *********************************/

typedef int	t_bool;
#define TRUE	1
#define FALSE	0

/********************************   Includes   ********************************/

#include "libft.h"
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>


/*********************************   Structs   ********************************/

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