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
# include <stddef.h>

/********************************   Funtions   ********************************/

// preparing functions
int			initialize(t_main *shell, char **env);
void		start_shell(t_main *shell);

// lexer	functions
void		lexer(t_main *shell);
int			tlist(t_tokens **head, char *arr);
int			token_check(t_main *shell);
void		listing_token(t_main *shell, char *tmp, size_t *j, char *token);
void		listing_rdr(t_main *shell, size_t *j, size_t *i, char *token);

// free		functions
void		free_env(t_env *shell);
void		free_double(char **arr);
void		free_tokens(t_main *shell);
void		free_command(t_main *shell, t_command *tp);
void		free_c(t_command *c);

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
t_main		*shell_keeper(t_main *shell);

// exits
void		exit_in_lex(t_main *shell);
void		exit_for_fork(t_main *shell);
void		exit_in_parser(t_main *shell, int in_here);
void		exit_in_exec(t_main *shell);
void		exit_in_expander(t_main *shell);

// expender functions
void		expender(t_main *shell);
char		*handle_dollar_sign(char *tmp, const char *token_value, size_t *i,
				t_main *shell);
char		*append_literal(char *tmp, char *token_value, size_t *start,
				size_t *i);
char		*createword(char *value, size_t *i);

// parser   functions
void		parser(t_main *shell, t_tokens *t, size_t i, t_command *cmds);
int			is_token(t_tokens *t);
size_t		rdr_count(char **str);
int			is_rdr(char *strs);
char		*allocate_result(const char *str);
void		toggle_quote(char c, t_bool *in_s, t_bool *in_d);
int			rdr_position(t_command *cmds);
size_t		length_to_token(t_tokens *lst);
size_t		find_word_end(const char *value, size_t start, t_bool *in_d,
				t_bool *in_s);
char		*remove_quotes(char *str, t_bool in_s, t_bool in_d);
char		**recreate_cmdval(t_command *cmd, size_t i, size_t j, size_t idx);

// executer functions
void		executor(t_main *shell, t_command *cmds, t_bool cmd_num, int i);
int			accessibility(t_command *cmds, t_main *shell);
int			opens(t_command *cmd, size_t *i, int fd);
void		close_all(t_command *cmds, int i);
void		wait_forks(t_main *shell, t_command *cmd);
int			heredocs(t_main *shell, t_command *cmd);
int			need_to_be_slash(char *value);
int			check_heredoc(t_command *cmd);

// builtins functions
int			cd(t_command *cmds, t_main *shell);
int			pwd(t_command *cmds, t_main *shell);
int			env(t_command *cmds, t_main *shell);
int			echo(t_command *cmds, t_main *shell);
int			unset(t_command *cmds, t_main *shell);
int			export(t_command *cmds, t_main *shell);
int			exit_cmd(t_command *cmds, t_main *shell);

// builtins utils functions
int			is_builtin(t_command *cmds, t_bool cmd_num, char *tmp, int i);
int			check_for_options(t_command *cmds);

#endif