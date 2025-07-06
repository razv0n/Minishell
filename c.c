#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
int main(int ac, char **av)
{
	int fd = open ("W=a6W,'5a", O_CREAT | O_RDWR, 0777);
	if (fd == -1)
		perror("bash :");
	else
		perror("bash :");
}
