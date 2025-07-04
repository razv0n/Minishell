#include <stdio.h> 
#include <signal.h>

int main(int ac, char **av)
{
#include <unistd.h>
signal(SIGINT, SIG_IGN);
execvp(av[1], av+1);
}
