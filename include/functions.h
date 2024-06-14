/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarac <ysarac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 06:28:23 by ysarac            #+#    #+#             */
/*   Updated: 2024/06/14 09:27:02 by ysarac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

/********************************   Includes   ********************************/

#include "defines.h"

/********************************   Funtions   ********************************/

// initialize functions
int initialize(t_main *shell, char **env);

// shell functions
void	start_shell(t_main *shell);

// utils functions
void	list_add_back(t_env **lst, t_env *tmp);
size_t	is_space(char *s);

// free functions
void	free_env(t_env *env);

// lexer functions
int lexer(t_main *shell);
#endif