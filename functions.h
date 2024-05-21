/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarac <ysarac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 22:19:29 by ysarac            #+#    #+#             */
/*   Updated: 2024/05/20 22:19:29 by ysarac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "defines.h"
# include <sys/types.h>

// preparing
int			initialize(t_main *shell, char **env);
void		start_shell(t_main *shell);

// lexer
int			lexer(t_main *shell);
t_tokens	*tlist(char **arr);
void		is_expendable(t_tokens *lst);
int			token_check(t_tokens *token);

// free
void		free_env(t_env *shell);
void		free_double(char **arr);
void		free_tokens(t_tokens *tokens);
void		main_free(t_main *shell);

// utils
char		**get_cmd(char **env);
void		list_add_back(t_env **lst, t_env *tmp);
size_t		is_space(char *s);
t_env		*find_env(t_env *envs, char *wanted);
size_t		wordcount(char *s);
size_t		wordlen(const char *str);
int			is_whitespace(char c);

// expender
int			expender(t_main *shell);
char		*handle_dollar_sign(char *tmp, const char *token_value, size_t *i,
				t_env *env);
char		*append_literal(char *tmp, char *token_value, size_t *start,
				size_t *i);
//
void		parser(t_main *shell);

#endif