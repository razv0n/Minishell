#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>


int main(int ac, char **av, char **env)
{
    char *arg[] = {"ls", NULL};
    execve("/usr/bin/ls", arg, NULL);
    printf("no\n");
    // char *cwd;
    // cwd = NULL;
    // getcwd(cwd, 200);
    // free (cwd);
    // return 0;
    // char *x = readline("test ");
    // (void)x;
    // free (x);
    return 0;
}
