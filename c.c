#include <stdio.h>
#include <unistd.h>
int main(int ac, char **av)
{
	close(1);
	execvp(av[1], av+1);
}
