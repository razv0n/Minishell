/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:04:22 by mfahmi            #+#    #+#             */
/*   Updated: 2025/05/09 11:39:10 by mfahmi           ###   ########.fr       */
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
	int	npi;
	int	pi[2];
	int	fd_in;
	bool	child;
	int	fd_out;
	int ext;
}	t_u;

typedef struct export
{
	char *str;
	struct export *next;
}	xp;

typedef struct t_info
{
    t_u     *utils;
    xp      *head_export;
    t_list  *head_env;
    t_list  *head_cmd;
    char *content;
    bool *joined;
    char *line;
}	t_info;

t_list	*ft_lstnew_d(void *content);
int     ft_strcmp(char *line, char *str);
int     check_metacharacter(const char  *c);
bool    check_quotes_error (t_info *info);
bool	free_print(t_list *head, char **words);
bool    check_error(t_list *head, char **words);
bool    is_redirect(char *c);
char	**ft_split_tokens(t_info *info);
bool    quotes_in_split(char quotes);
bool    is_pipe(char *c);
bool    check_metacharcter_skip(const char *c, size_t *i);
bool	is_whitespace(char c);
bool	check_quotes(char c);
void	is_joined(char *s, t_info *info);
void	ft_lstadd_back_d(t_list **start, t_list *new);
void    handle_sigint(int sig);
void	ft_lstadd_front_d(t_list **lst, t_list *new);
void    split_arg(t_info *info);
void	ft_lstclear_d(t_list **lst);
void    print_stack( t_list *head_cmd, t_info *info);// for testing u should remove it
void    type_tokens(t_list *head);
void    init_info(t_info *info);
void    expand(t_info *info);
void    cpy_env(char **env, t_info *info);
void    remove_node (t_list **head, t_list *remove);
void    remove_the_null(t_list **head);
char	**fr_mem_split(int index, char **result);
// char	**ft_split_tokens(char const *s);
void	redirection(char *str, int cdt);
void	init_things(t_info *info, t_list *head);
// void	init_things(t_list *head, t_u *utils);
void ft_free(t_info *info);
void	ft_env(t_list *head_env, char **cmd);
void	ft_echo(char **arg);
void	ft_cd(t_info *info, char **arg);
void	ft_pwd(void);
int    pars(t_info *info);
void	ft_pwd(void);
void	ft_export(xp **head, t_info *info);
void	ft_unset(t_info *info, char **cmd);
// void	ft_cd(t_info *info);
// void	ft_echo(char **cmd);
void	ft_exit(char **cmd, int *ext, int child);
void	create_export(t_info *info, char **env, int i);
void	add_to_env(t_list **head, char *s);
int	length(char *s);
int	compare(char *s1, char *s2, int bl);
void	where_to_edit(xp **tmp, xp **ptr, char *s);
char	*join_str(char *s1, char *s2);

#endif