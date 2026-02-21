/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamdjar <bamdjar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 02:44:09 by bamdjar           #+#    #+#             */
/*   Updated: 2025/09/08 04:01:20 by bamdjar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

# define PROMT "shell$ "

typedef struct s_token	t_token;
typedef struct s_env	t_env;
typedef struct s_card	t_card;

typedef enum e_token_type
{
	WORD,
	PIPE,
	RIN,
	ROUT,
	AP,
	HER,
	SQ,
	DQ,
}						t_token_t;

typedef enum e_quote_state
{
	NORMAL,
	IN_SQUOTE,
	IN_DQUOTE,
}						t_quote_state;

typedef struct s_token
{
	t_token_t			type;
	char				*value;
	int					append;
	t_quote_state		quote_ctx;
	t_token				*next;
}						t_token;

typedef struct s_env
{
	char				*var;
	char				*value;
	int					exported;
	struct s_env		*next;
}						t_env;

typedef struct s_card
{
	char				*cmd;
	char				**args;
	int					fd0;
	int					fd1;
	t_token				*tokens;
	struct s_card		*next;
}						t_card;

typedef struct s_snail
{
	t_env				*env;
	t_token				*tokens;
	t_card				*cards;
	int					exit_code;
	int					fd_in;
	int					fd_out;
	int					in_heredoc;
}						t_snail;

typedef struct s_splice_params
{
	t_token				**head;
	t_token				*prev;
	t_token				*current;
	t_token				*new_list;
}						t_splice_params;

typedef struct s_qoute
{
	size_t				i;
	size_t				j;
	t_quote_state		state;
	char				quote_char;
}						t_quote_context;

bool					is_valid(char *input);
t_snail					*shell(void);
void					cleanup_shell(void);
int						parser(char *input);
int						ft_strcmp(const char *s1, const char *s2);
int						syntax_checker(t_token *tokens);
void					free_tokens(t_token *tokens);
void					handle_sigint(int sig);
void					save_signals_for_heredoc(t_snail *snail);
void					restore_signals_after_heredoc(t_snail *snail);
void					save_signals_for_fork(t_snail *snail);
void					restore_signals_after_fork(t_snail *snail);

void					build_env(t_env **env, char **envp);
t_card					*build_cards(t_token *tokens);
void					free_table(char **table);
char					*buscando_env(char *var, t_env *env);
t_env					*buscando_node(char *var, t_env *env);

int						process_heredocs(t_snail *snail);
int						redir(t_snail *snail);
void					free_pcard(t_card **head);
void					cleanup_card_fds(t_card *cards);

void					expand_tokens(t_snail *snail);
void					expand_token_list(t_token **tokens, t_snail *snail);
char					*expand_vars(char *line, t_snail *snail);
void					expand_card_tokens(t_card *card, t_snail *snail,
							char *expanded);
int						should_expand_token(t_token *token);
char					*expand_single_variable(const char *str,
							t_snail *snail);
t_token					*split_expanded_token(const char *expanded_str,
							t_token_t original_type);
t_token					*splice_tokens(t_splice_params *params, t_token *next);
t_token					*create_token_node(char *value, t_token_t type);
int						has_variable(char *str);
int						get_var_name_len(const char *str);
char					*extract_var_name(const char *str);
char					*get_var_value(const char *var_name, t_snail *snail);
char					*append_and_free(char *base, const char *add);
char					*remove_quotes_from_expanded(const char *str);
char					*remove_quotes(char *value, t_token_t *type);
char					*process_quote_removal(char *value, char *dst,
							int *state);

void					fill_cmd_and_args(t_card *card);
void					setup_all_cards(t_snail *snail);
int						ft_isdigit_str(char *str);

void					execution(t_snail *snail);
int						exec_one(t_snail *snail, t_card *card);
void					setup_child_redir(t_snail *snail, int prev_fd,
							t_card *card, int *pipe_fd);
bool					is_directory(const char *path);
void					handle_execve_error(t_card *card, char *path,
							char **envp);
char					*buscando_path(char *cmd, t_env *env);
char					**env_to_table(t_env *env);
void					validate_path(char *path, t_card *card);
int						handle_parent_process(t_snail *snail, pid_t pid);
void					exec_external_command(t_card *card, t_snail *snail);
void					handle_process_status(t_snail *snail, int last_pid,
							int *status);
int						execute_pipeline_command(t_snail *snail, t_card *card,
							int prev_fd, int *pipe_fd);
void					process_pipeline_card(t_snail *snail, t_card *card,
							int *prev_fd, int *final_pid);

void					ft_error(char *str);
void					ft_error3(char *str1, char *str2, char *str3);
void					redir_help(t_snail *snail, int prev_fd, t_card *card,
							int *pipe_fd);

bool					blt(t_card *card);
int						myblts(t_card *card, t_snail *snail);
int						echo_blt(t_card *card);
int						cd_blt(t_card *card, t_env **env);
int						pwd_blt(t_card *card);
int						export_blt(t_card *card, t_env **env);
int						unset_blt(t_card *card, t_env **env);
int						env_blt(t_card *card, t_env *env);
void					add_to(t_env **env, t_env *new_node);
t_env					*new_node(char *var, char *value);
int						exit_blt(t_card *card, t_snail *snail);
int						has_quoted_content(const char *str);

#endif
