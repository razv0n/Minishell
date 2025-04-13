#include "../Minishell.h"

void    hash(char *line) //* check hash # if we found it we dont care about quotes for example $> #sdf '""       - > this is not a syntax error
{
    int i;
    char *tmp;

    i = 0;
    while (line[i]) //*  ls# this is syntax error
    {
        if (line[0] == '#' || ((line[i] == ' ' || line[i] <= '\t') && line[i + 1] == '#'))
        {
            tmp = line;
            line = ft_substr(line, i, ft_strlen(line));
            free(tmp);
            break;
        }
        i++;
    }
}

void check_quotes (char *line)
{
    int i;
    int j;
    char *stack;

    stack = malloc(ft_strlen(line) / 2); //! stack algo
    i = 0;
    j = 0;
    while (line[i])
    {
        if (line[i] == '\'')
        {
            stack[j] = line[i]; //
            j++;
        }
        else if (line[i] == '"')
        {

            j++;
        }
    }
}