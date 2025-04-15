#ifndef MINISHELL_H
#define MINISHELL_H

#include <readline/readline.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include "libft/libft.h"
typedef struct t_node
{
    char *content;
    struct t_node *next;
    struct t_node *prev;
}t_node;
void check_quotes (char *line);
#endif