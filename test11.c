#include "Minishell.h"


int main(int ac , char **av , char **env)
{
    static int  index = 2;
    int a = 2;
    pid_t id;
    switch (id = fork())
    {
        case -1:
            perror("fork");
            exit (1);
        case 0:
            index++;
            a++;
        default:
            sleep(3);
            break;
    }
    printf("index = %d a = %d\n", index, a);
}