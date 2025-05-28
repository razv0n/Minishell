#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>

void handler(int sig)
{
	printf("sig pipe");
	exit (1);
}

int main(int ac, char **av, char **env)
{
	int pid, pid2, status;
	int ppfd[2];

	signal(SIGPIPE, handler);
	pipe(ppfd);
	pid = fork();
	if (pid == 0)
	{
		dup2(ppfd[1], 1);
		close(ppfd[1]); 
		close(ppfd[0]);
		char	*s[] = {"ls", "-la", NULL};
		execve("/usr/bin/ls", s, env);
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		dup2(ppfd[0], 0);
		close(ppfd[1]);// ! write end
		close(ppfd[0]); //! read end
		// char buf[] = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
		// while (1)
		// 	write (ppfd[1], buf, 41);
		char	*s[] = {"grep", "a", NULL};
		execve("/usr/bin/grep", s, env);
	}
	// printf("start \n");
	 int i = 10;
	 write (1, &i, sizeof(int));
	// while(i < 100000000)
	// {
	// 	// printf("%d\n", i);
	// 	i++;
	// }
	printf("done\n");
	close(ppfd[0]);
	close(ppfd[1]);
	waitpid(pid2, &status, 0);
	wait(NULL);
	//wait(NULL);
}
