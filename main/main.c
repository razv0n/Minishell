#include "../Minishell.h"

void print_stack()
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
        line = readline("╭━━[\033[1;36mminishell\033[0m]━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╮\n╰──➤");
        if (!line)
            return (1);
        pars(line);
        free(line);
    }
    return (0);
}
