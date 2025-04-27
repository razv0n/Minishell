#include "Minishell.h"


void    handler(int sig)
{
    printf("\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

int main (int ac, char **av, char **env)
{
    signal(SIGINT, handler);
    while (1)
    {
        int i = 0;
        char * line  = readline("$> ");
        if (line[0] == 'e')
        {
            while (env[i])
            {
                printf("%s", env[i]);
                i++;
            }
            printf("\n");
        }
        if(!line)
        {
            printf("exit\n");
            exit(0);
        }
        free(line);
    }
}