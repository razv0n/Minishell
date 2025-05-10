#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <wait.h>


// void    handle(int sig)
// {
//     (void)sig;
//     printf("recieved SIGPIPE\n");
// }

// int main()
// {
//     int pi[2];
//     if (pipe(pi) == -1)
//         return (1);
//     signal(SIGPIPE, handle);
//     int n = 9;
//     int b = 0;
//     write (pi[1], &n, sizeof(int));
//     read (pi[0], &b, sizeof(int));
//     close (pi[0]);
//     close (pi[1]);
//     printf("%d\n", b);
//     return (0);
// }

int main()
{
    int id;
    id = fork();
    if (!id)
    {
        write (2, "moncef chefnaj\n", 15);
    }
    return 0;
    // int pi[2];
    // if (pipe(pi) == -1)
    //     return (1);
    // printf("read = %d  write = %d\n", pi[0], pi[1]);
    // printf("read = %d  write = %d\n", pi[2], pi[3]);
    // close (pi[0]);
    // close (pi[1]);
    // if (pipe(pi) == -1)
    //     return (1);
    // printf("read = %d  write = %d\n", pi[0], pi[1]);
    // close (pi[0]);
    // close (pi[1]);
    // close (pi[2]);
    // close (pi[3]);
    // char *cmd = NULL;
    // printf("%s\n", getcwd(cmd, 1024));
    // char *arg[] = {"cd", "../", NULL};
    // int id;
    // if (id = fork() == -1)
    //     return (1);
    // if (!id)
    // {
    //     if (execve(arg[0], arg, NULL) == -1)
    //         return (100);
    // }
    // else
    // {
    //     waitpid(id, NULL, 0);
    //     printf("%s\n", getcwd(cmd, 1024));
    // }
    // printf("hey\n");
    // char *p = getenv("PATH");
    // printf("%s\n", p);
//     return (0);
}
