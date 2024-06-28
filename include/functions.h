/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarac <ysarac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 06:28:23 by ysarac            #+#    #+#             */
/*   Updated: 2024/06/28 13:16:48 by ysarac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

/********************************   Includes   ********************************/

# include "defines.h"

/********************************   Funtions   ********************************/

// preparing functions
int			initialize(t_main *shell, char **env);
void		start_shell(t_main *shell);

// lexer	functions
int			lexer(t_main *shell);
int			tlist(t_tokens **head, char *arr);
int			token_check(t_main *shell);
void		listing_squote(t_main *shell, char *tmp, size_t *j, char *token);
void		listing_dquote(t_main *shell, char *tmp, size_t *j, char *token);
void		listing_token(t_main *shell, char *tmp, size_t *j, char *token);
void		listing_rdr(t_main *shell, char *tmp, size_t *j, size_t *i,
				char *token);

// free		functions
void		free_env(t_env *shell);
void		free_double(char **arr);
void		free_tokens(t_main *shell);
void		free_command(t_main *shell);

// utils	functions
char		**get_cmd(t_env *env);
void		list_add_back(t_env **lst, t_env *tmp);
size_t		is_space(char *s);
t_env		*find_env(t_env *envs, char *wanted);
size_t		wordcount(char *s);
size_t		wordlen(const char *str);
int			is_whitespace(char c);
size_t		t_lst_size(t_tokens *t);
void		syntax_message(int flag);
void		signal_reciever(int flag);

// expender functions
int			expender(t_main *shell);
char		*handle_dollar_sign(char *tmp, const char *token_value, size_t *i,
				t_env *env);
char		*append_literal(char *tmp, char *token_value, size_t *start,
				size_t *i);
// parser   functions
int			parser(t_main *shell, t_tokens *t, size_t i);
int			is_token(t_tokens *t);
size_t		rdr_count(char **str);
int			is_rdr(char *strs);

// executer functions
int			executor(t_main *shell);
int			is_builtin(t_command *cmds, t_main *shell, t_bool cmd_num);
int			accessibility(t_command *cmds, t_main *shell);
void		close_fd(t_command *cmds, int flag);

// builtins functions
void		echo(t_command *cmds, t_main *shell);
void		cd(t_command *cmds, t_main *shell);
void		pwd(t_command *cmds, t_main *shell);
void		env(t_command *cmds, t_main *shell);
void		unset(t_command *cmds, t_main *shell);
void		export(t_command *cmds, t_main *shell);
void		exit_cmd(t_command *cmds, t_main *shell);


#endif