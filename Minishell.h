#ifndef MINISHELL_H
#define MINISHELL_H

#include <readline/readline.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include "libft/libft.h"
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
};//* this enum for type of token

typedef struct t_info
{
    char *content;
    char *stdin;
    char *stdout;
}t_info;

void    check_quotes (char *line);
bool    quotes_in_split(char quotes);
char	**fr_mem_split(int index, char **result);
void    pars(char *line, t_list **head);
char	**ft_split_tokens(char const *s);
void	ft_lstadd_front_d(t_list **lst, t_list *new);
void	ft_lstadd_back_d(t_list **start, t_list *new);
t_list	*ft_lstnew_d(void *content);
void    split_arg(char *line, t_list **head);
int     check_metacharacter(const char  *c);
int     ft_strcmp(char *line, char *str);
void	ft_lstclear_d(t_list **lst);
bool	free_print(t_list *head, char **words);
void    handle_sigint(int sig);
bool    check_error(t_list *head, char **words);
void    print_stack(t_list *head);// for testing u should remove it
void    type_tokens(t_list *head);
bool    is_redirect(char *c);
bool    is_pipe(char *c);
bool    check_metacharcter_skip(const char *c, size_t *i);
#endif