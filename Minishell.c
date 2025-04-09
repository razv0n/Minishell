#include "Minishell.h"
int main (int ac , char **av)
{
    char *line;
    while (1)
    {
        line = readline("$> ");
        printf ("%s\n", line);
    }
    return 0;
}