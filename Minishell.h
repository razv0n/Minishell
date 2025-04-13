#ifndef MINISHELL_H
#define MINISHELL_H

#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbol.h>
#include "libft/libft.h"
typedef struct t_node
{
    char **content;
    struct t_node *next;
};

#endif