#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>

int main()
{
    // char *cwd;

    // cwd = NULL;
    // getcwd(cwd, 200);
    // free (cwd);
    // return 0;
    char *x = readline("test ");
    // (void)x;
    free (x);
    return 0;
}