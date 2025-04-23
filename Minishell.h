#ifndef MINISHELL_H
#define MINISHELL_H

#include <readline/readline.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include "libft/libft.h"
enum e_type
{
    TYPE_WORD,
    TYPE_PIPE,
    TYPE_REDIRECT_IN,
    TYPE_REDIRECT_OUT,
    TYPE_HEREDOC,
    TYPE_APPEND,
};//* this enum for type of token
// typedef struct t_list
// {
//     char *content;
//     int type;
//     struct t_list *next;
//     struct t_list *prev;
// }t_list; // this is for parsing
void    check_quotes (char *line);
bool    quotes_in_split(char quotes);
char	**fr_mem_split(int index, char **result);
void    pars(char *line, t_list *head);
char	**ft_split_tokens(char const *s);
void	ft_lstadd_front_d(t_list **lst, t_list *new);
void	ft_lstadd_back_d(t_list **start, t_list *new);
t_list	*ft_lstnew_d(void *content);
void    split_arg(char *line, t_list *head);
#endif