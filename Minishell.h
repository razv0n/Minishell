/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:04:22 by mfahmi            #+#    #+#             */
/*   Updated: 2025/05/10 16:23:32 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <wait.h>
# include <stdbool.h>
# include "libft/libft.h"
# include <signal.h>
# include <readline/history.h>
# include <errno.h> 
enum e_type
{
    WORD,
    PIPE,
    REDIRECT_IN,
    REDIRECT_OUT,
    HEREDOC,
    APPEND,
    SINGLE_Q,
    DOUBLE_Q,
};//* this enum for type of token

typedef enum {
    EXEC_BUILTIN,
    EXEC_EXTERNAL,
    EXEC_FAILURE
} t_exec_type;

typedef enum {
    SYNTAX_ERROR,
    FR_CHILD,
} t_error_type;

# define ERR_MALLOC	"malloc error\n"
# define ERR_PIPE	"pipe error\n"
# define ERR_FORK	"fork error\n"

# define EXT_MALLOC	1
# define EXT_PIPE	1
# define EXT_FORK	1

typedef struct utils
{
	char	**path;
	char	**cmd;
	char	*exc;
	int	check;
	int	copy;
    bool is_pip;
	int	npi;
	int	pi[2];
	int	fd_in;
	int	fd_out;
    int ext;
}	t_u;

typedef struct export
{
	char *str;
	struct export *next;
}	xp;

typedef struct s_l
{
    void            *content;
    struct s_l      *next;
}	t_ptr;

typedef struct t_ptr
{
    t_u     *utils;
    xp      *head_export;
    t_list  *head_env;
    t_list  *head_cmd;
    char **words;
    bool *joined;
    char *line;
}	t_info;

t_list	*ft_lstnew_d(void *content);
int     ft_strcmp(char *line, char *str);
int     check_metacharacter(const char  *c);
bool    check_quotes_error (t_info *info);
bool    check_error(t_info *info); 
bool    is_redirect(char *c);
char	**ft_split_tokens(t_info *info);
bool    quotes_in_split(char quotes);
bool    split_arg(t_info *info);
bool    is_pipe(char *c);
bool    check_metacharcter_skip(const char *c, size_t *i);
bool	is_whitespace(char c);
bool	check_quotes(char c);
void	is_joined(char *s, t_info *info);
void	ft_lstadd_back_d(t_list **start, t_list *new);
void    handle_sigint(int sig);
void	ft_lstadd_front_d(t_list **lst, t_list *new);
void    ft_free(t_info *info, t_error_type err);
void	ft_lstclear_d(t_list **lst);
void    type_tokens(t_list *head);
void    init_info(t_info *info);
void    expand(t_info *info);
void	free_path(char **path);
void    cpy_env(char **env, t_info *info);
void    remove_node (t_list **head, t_list *remove);
void    remove_the_null(t_list **head);
char	**fr_mem_split(int index, char **result);
// char	**ft_split_tokens(char const *s);
void	redirection(char *str, int cdt);
void	init_things(t_info *info, t_list *head);
void   *ft_malloc (size_t size);


// void	init_things(t_list *head, t_u *utils);
void	ft_env(t_list *head_env);
void	ft_exit(char **cmd, int ext);
int	length(char *s);

void	ft_echo(char **arg);
void	ft_cd(char **arg);
void	ft_pwd(void);
int change_red(t_info *info);
int    pars(t_info *info);
void print_stack(t_list *head); // remove it
void	ft_lstclear_not(t_list **lst);
void ft_free_all(t_info *info);
t_ptr	*ft_lstnew_ptr(void *content);
void	ft_lstadd_back_ptr(t_ptr **start, t_ptr *new);
// void	ft_pwd(void);
// void	ft_export(t_info *info);
// void	ft_unset(t_info *info);
// void	ft_cd(t_info *info);
// void	ft_echo(char **cmd);
// void	ft_exit(char **cmd);

#endif