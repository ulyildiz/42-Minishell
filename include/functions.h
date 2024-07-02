/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 06:28:23 by ysarac            #+#    #+#             */
/*   Updated: 2024/06/29 17:31:49 by ulyildiz         ###   ########.fr       */
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
void		listing_token(t_main *shell, char *tmp, size_t *j, char *token);
void		listing_rdr(t_main *shell, size_t *j, size_t *i, char *token);
void		exit_in_lex_ex(t_main *shell);

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
size_t		wordlen(const char *str);
int			is_whitespace(char c);
size_t		t_lst_size(t_tokens *t);
void		syntax_message(int flag);
void		signal_reciever(int flag);
int			update_env(t_main *shell);
void		disable_echo_control_chars(void);
void		exit_for_fork(t_main *shell);

// expender functions
int			expender(t_main *shell);
char		*handle_dollar_sign(char *tmp, const char *token_value, size_t *i,
				t_main *shell);
char		*append_literal(char *tmp, char *token_value, size_t *start,
				size_t *i);

// parser   functions
int			parser(t_main *shell, t_tokens *t, size_t i);
int			is_token(t_tokens *t);
size_t		rdr_count(char **str);
int			is_rdr(char *strs);
void		exit_in_parser(t_main *shell);
char		*allocate_result(const char *str);
void		toggle_quote(char c, t_bool *in_s, t_bool *in_d);
int			rdr_position(t_command *cmds);
char		*remove_quotes(const char *str, t_bool in_s, t_bool in_d);
char		*extract_cleaned_substr(const char *value, size_t start, size_t end);
size_t		length_to_token(t_tokens *lst);
size_t		find_word_end(const char *value, size_t start, t_bool *in_d,
					t_bool *in_s);
// executer functions
int			executor(t_main *shell, t_command *cmds, t_bool cmd_num, int i);
int			accessibility(t_command *cmds, t_main *shell);
int			opens(t_command *cmd, size_t *i);
void		close_all(t_command *cmds, int i);

// builtins functions
void		cd(t_command *cmds, t_main *shell);
void		pwd(t_command *cmds, t_main *shell);
void		env(t_command *cmds, t_main *shell);
void		echo(t_command *cmds, t_main *shell);
void		unset(t_command *cmds, t_main *shell);
void		export(t_command *cmds, t_main *shell);
void		exit_cmd(t_command *cmds, t_main *shell);

// builtins utils functions
int			is_builtin(t_command *cmds, t_main *shell, t_bool cmd_num);
t_env		*sort_export(t_env *lst, int (*cmp)(int, int));
int			ascending(int a, int b);
char		*append_path(char *base,char *append);
t_env		*update_or_create_env(t_env **envs, char *name, char *value);
int			set_env_value(t_env *env, char *value);
t_env		*create_env(char *name, char *value);

#endif