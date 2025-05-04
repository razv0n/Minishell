/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:04:22 by mfahmi            #+#    #+#             */
/*   Updated: 2025/05/04 10:31:25 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <readline/readline.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../libft/libft.h"
#include <signal.h>
#include<readline/history.h>

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

# define ERR_MALLOC	"malloc error\n"
# define ERR_PIPE	"pipe error\n"
# define ERR_FORK	"fork error\n"

# define EXT_MALLOC	1
# define EXT_PIPE	1
# define EXT_FORK	1

typedef struct t_info
{
    t_u     *utils;
    xp      *head_export;
    t_list  *head_env;
    t_list  *head_cmd;
    char *content;
    char *line;
}t_info;

t_list	*ft_lstnew_d(void *content);
int     ft_strcmp(char *line, char *str);
int     check_metacharacter(const char  *c);
bool    check_quotes_error (t_info *info);
bool	free_print(t_list *head, char **words);
bool    check_error(t_list *head, char **words);
bool    is_redirect(char *c);
bool    quotes_in_split(char quotes);
bool    is_pipe(char *c);
bool    check_metacharcter_skip(const char *c, size_t *i);
bool	is_whitespace(char c);
bool	check_quotes(char c);
void	ft_lstadd_back_d(t_list **start, t_list *new);
void    pars(t_info *info, char *line, char **env);
void    handle_sigint(int sig);
void	ft_lstadd_front_d(t_list **lst, t_list *new);
void    split_arg(t_info *info);
void	ft_lstclear_d(t_list **lst);
void    print_stack(t_list *head);// for testing u should remove it
void    type_tokens(t_list *head);
void    init_info(t_info *info, char *line, char **env);
void    expand(t_info *info);
void    cpy_env(char **env, t_info *info);
void    remove_node (t_list **head, t_list *remove);
void    remove_the_null(t_list **head);
char	**fr_mem_split(int index, char **result);
char	**ft_split_tokens(char const *s);

#endif