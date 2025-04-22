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
typedef struct t_node
{
    char *content;
    int type;
    struct t_node *next;
    struct t_node *prev;
}t_list; // this is for parsing
void    check_quotes (char *line);
bool    quotes_in_split(char quotes);
#endif