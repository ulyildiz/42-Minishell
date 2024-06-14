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

/*********************************   Structs   ********************************/

// enviromments structs
typedef struct	s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

// main shell struct
typedef struct s_main
{
	t_env		*envs; //envler için
	//t_tokens	*token; //token listesi (whitespacelere ve tokenlere göre splitli
	//t_command	*cmd;
	int			control;
	char		**paths; // komutlar için parçalanmış pathler
	char		*prompt; // frelenecek bir değer
	char		**env_for_execve_function;
	char		*cmd_line; // komut satırından okunan satır
}   t_main;


#endif