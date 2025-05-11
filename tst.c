#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>

int main()
{
    pid_t pid = fork();
    if (pid == -1)
     {
        perror("Frok");
        return -1;
    }
    else if (pid == 0)
    {
        sleep(5);
        printf("finish executing\n");
        return 0;
    }
    pid = fork();
    if (pid == -1)
    {
        perror("Fork");
        return -1;
    }
    else if (pid == 0)
    {
        sleep(5);
        printf("finish executing\n");
        return 0;
    }
    return 0;
}