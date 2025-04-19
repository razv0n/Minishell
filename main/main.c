#include "../Minishell.h"

int main (int ac , char **av, char **env)
{
    char *line;
    if (ac != 1)
    {
        printf ("minishell cannot run this\n");
        exit(1);
    }
    while (1)
    {
        line = readline("$> ");
        if (!line)
            return (1);
        lexer(line);
        free(line);
    }
    return (0);
}