#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
// void	handler(int sig)
// {
// 	printf("sig pipe");
// 	exit(1);
// }



// int main()
// {
// 	int fd = 0;

// 	fd = dup(fd);
// 	pritnf("fd = %d \n", fd);
// 	ft_putstr_fd(fd, fd);
// 	// fprintf(fd, "moncef \n");
// }

int main ()
{
	int fd;
	fd = open("moncef", O_CREAT | O_RDWR, 0777);
	if (fd == -1)
		perror("MInishell"); // -> errno
	if (dup2(fd, 1) == -1)
		perror("minihsell");
	close(fd);
	printf("moncef file\n");
}
// void	ft_pipe(int pip[2])
// {
// 	int		*ptr_fd;

// 	if (pipe(pip) == -1)
// 		printf("no such file or dir");
// 		// ft_free_all(NORMAL, 2);
// 	// ptr_fd = ft_malloc(sizeof(int) * 2, SECOUND_P);
// 	// *ptr_fd = pip[0];
// 	// *(ptr_fd + 1) = pip[1];
// 	// add_ptr(ptr_fd, return_ptr(), FIRST_P, CLOSE);
// }

// int main ()
// {
// 	int pip[2];
// 	char *fd_read;

// 	fd_read = malloc(sizeof(char) * 20);
// 	// fd_read = malloc(sizeof(char) * 19);
// 	ft_pipe(pip);
// 	printf("%d   <=>  %d\n", pip[0], pip[1]);
// 	write(pip[1], "moncef  is the best", 19);
// 	read(pip[0], fd_read, 19);
// 	fd_read[19] = '\0';
// 	printf("%s", fd_read);
// }
// int	main(int ac, char **av, char **env)
// {
// 	int	ppfd[2];
// 		char *s[] = {"ls", "-la", NULL};
// 		char *s[] = {"grep", "a", NULL};
// 	int	i;

// 	int pid, pid2, status;
// 	signal(SIGPIPE, handler);
// 	pipe(ppfd);
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		dup2(ppfd[1], 1);
// 		close(ppfd[1]);
// 		close(ppfd[0]);
// 		execve("/usr/bin/ls", s, env);
// 	}
// 	pid2 = fork();
// 	if (pid2 == 0)
// 	{
// 		dup2(ppfd[0], 0);
// 		close(ppfd[1]); // ! write end
// 		close(ppfd[0]); //! read end
// 		// char buf[] = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
// 		// while (1)
// 		// 	write (ppfd[1], buf, 41);
// 		execve("/usr/bin/grep", s, env);
// 	}
// 	// printf("start \n");
// 	i = 10;
// 	write(1, &i, sizeof(int));
// 	// while(i < 100000000)
// 	// {
// 	// 	// printf("%d\n", i);
// 	// 	i++;
// 	// }
// 	printf("done\n");
// 	close(ppfd[0]);
// 	close(ppfd[1]);
// 	waitpid(pid2, &status, 0);
// 	wait(NULL);
// 	// wait(NULL);
// }
