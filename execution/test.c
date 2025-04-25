#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    char *arg[] = {"cat", "start_executing.c", "-e", NULL};
    execve("/usr/bin/cat", arg, NULL);
    printf("hey\n");
    // char *p = getenv("PATH");
    // printf("%s\n", p);
    return (0);
}
