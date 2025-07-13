/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:04:22 by mfahmi            #+#    #+#             */
/*   Updated: 2025/07/13 19:45:30 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <termios.h>
# include <unistd.h>
# include <wait.h>

typedef enum err
{
	SYNTAX_ERROR,
	ERR_CHILD,
	ERR_MALLOC,
	NORMAL,
	EXIT,
	ERR_EXECVE,
	ERR_AMBIGUOUS,
	SYSCALL,
	HERE_DOCUMENT,
	CHILD
}					t_error_type;

typedef enum type
{
	EXEC_BUILTIN,
	EXEC_EXTERNAL,
	EXEC_FAILURE
}					t_exec_type;

typedef enum err_sys
{
	SYS_FAIL = -1,
	SYS_SUCCESS
}					t_sys_err;

typedef struct utils
{
	char			**path;
	char			**cmd;
	char			*exc;
	char			*str_heredoc;
	int				check;
	int				copy;
	int				npi;
	int				pi[2];
	bool			i;
	bool			child;
	int				fail;
	char			*str_fail;
	int				id;
	int				error;
	bool			bin;
}					t_u;

typedef struct export
{
	char			*str;
	struct export	*next;
	struct export	*prev;
}		t_xp;

typedef struct s_l
{
	void			*content;
	t_free_type		place;
	t_free_type		type;
	struct s_l		*next;
}					t_ptr;

typedef struct s_info
{
	t_u				*utils;
	t_xp			*head_export;
	t_list			*head_env;
	t_list			*head_cmd;
	char			**env;
	char			*line;
	int				ext;
	int				wt;
	int				fd_in;
	int				fd_out;
	char			**path_name;
	int				count_herdoc;
	bool			*joined;
	bool			permi;
	char			*cw;
	bool			sigint_herdoc;
}					t_info;

t_list				*ft_lstnew_d(void *content, t_free_type place);
int					ft_strcmp(char *line, char *str);
int					check_metacharacter(const char *c);
void				exit_status(t_info *info);
bool				check_quotes_error(t_info *info);
bool				check_error(t_info *info);
bool				is_redirect(char *c);
void				ft_free(t_error_type msg);
t_sys_err			rdr_in(char *str);
t_sys_err			rdr_herdoc(t_info *info);
t_sys_err			rdr_append(char *str);
t_sys_err			rdr_out(char *str);
int					ft_dupx(int fd1, int fd2, bool is_dup2);
char				*go_to_expand(char *str, t_list *head_env);
t_sys_err			init_info(t_info *info);
int					ft_open(char *str, int flag, int permi);
t_ptr				*where_is_fd(t_ptr *head, int fd);
bool				have_space(char *str);
void				*ft_malloc(size_t size, t_free_type place,
						t_free_type type);
void				help_norm(char **str, t_list *head);
char				*check_to_expand(char *str, int *i, t_info *info);
char				*cas_in_expand(char *str, int *i, t_info *info);
char				**ft_split_tokens(t_info *info);
void				add_ptr(void *ptr, t_ptr **head, t_free_type place,
						t_free_type type);
bool				quotes_in_split(char quotes);
bool				*sig_varible(void);
void				remove_quote(t_list *head);
void				remove_the_null(t_list **head);
t_sys_err			fail_sys_call(t_info *info);
int					count_herdoc(t_list *head);
bool				split_arg(t_info *info);
void				ft_free_all(t_error_type msg, int exit_code);
void				is_joined(char *s, int length, t_info *info);
t_sys_err			herdoc(char *str, t_info *info, t_type_word is_quotes);
void				change_red_help(t_list **head, t_info *info);
char				*ft_getenv(char *nm_varible, t_list *env);
void				ft_lstclear_d(t_list *lst);
char				*type_red(t_list *head, t_info *info);
bool				type_red2(t_list *head, char **str, t_info *info,
						t_type_word wich_quotes);
bool				is_pipe(char *c);
bool				check_metacharcter_skip(const char *c, size_t *i);
void				handle_sig(int sig);
bool				is_whitespace(char c);
void				remove_quotes(char **str, t_list *node);
bool				check_quotes(char c);
char				*joined_node_str(t_list *head, bool *is_quotes);
void				unlink_path(char **path_name);
void				expand(t_info *info);
void				expand_2(char **str, t_type_word wich_quote, t_info *info);
void				ft_lstclear_not(t_ptr **lst, bool child_herdoc);
void				ft_lstadd_back_d(t_list **start, t_list *new);
t_sys_err			start_herdoc(t_info *info, t_list *head);
t_sys_err			path(t_info *info);
t_sys_err			ft_pipe(int pip[2]);
t_sys_err			ft_close(int fd);
int					ft_dupx(int fd1, int fd2, bool is_dup2);
void				ft_lstadd_front_d(t_list **lst, t_list *new);
void				type_tokens(t_list *head);
void				cpy_env(char **env, t_info *info);
t_ptr				**return_ptr(void);
bool				check_if(t_type_word wich_quote, t_list *node,
						bool *joined);
void				remove_node_single(t_ptr **head, t_ptr *remove);
void				split_variable(t_type_word wich_quote, t_list **node);
void				ft_lstclear_ptr(t_ptr **lst);
void				ft_perror(t_error_type msg);
int					pars(t_info *info);
void				setup_signals(void);
void				ft_lstclear_ptr(t_ptr **lst);
int					compare(char *s1, char *s2, bool b1, bool b2);
int					length(char *s);
void				remove_node_doubly(t_list **head, t_list *remove);
t_ptr				*ft_lstnew_ptr(void *content);
void				ft_lstadd_back_ptr(t_ptr **start, t_ptr *new);
char				**collecte_cmds(t_list *head);

/*		>------------------ Execution ------------------<		*/
t_sys_err			redirection(t_list *node, int cdt, t_info *info);
void				init_things(t_info *info, t_list *head);
t_sys_err			execute_cmd(t_info *info, int cdt);
// int					check_access(t_info *info);
void				check_access(t_info *info);
char				*add_string(char *s1, char *s2);
char				**update_path(char *s);
int					count_pipes(t_list *head);
int					check_builtin(t_info *info, char **cmd);
void				create_export(t_info *info, char **env, int i);
int					where_to_edit(t_xp **tmp, t_xp **ptr, char *s);
void				add_to_env(t_list **head, char *s);
char				*join_str(char *s1, char *s2, int cdt, int *equal);
void				attach_node(t_xp **head, char *s);
t_xp				*create_node(char *s);
int					add_to_export(t_xp **head, char *s, t_info *info);
void				check_which_msg(char *cmd, t_info *info);
int					complete_check(char **path, t_info *info);
t_sys_err			back_to_normal(t_info *info);
void				get_next_cmd(t_info *info, t_list **head);
// built-in

void				ft_pwd(t_info *info);
void				ft_cd(t_info *info, char **arg);
void				ft_env(t_list *head_env, char **cmd, t_info *info);
void				ft_export(t_xp **head, t_info *info);
void				ft_unset(t_info *info, char **cmd);
void				ft_echo(char **cmd, t_info *info);
void				ft_exit(char **cmd, int *ext, int child);

#endif