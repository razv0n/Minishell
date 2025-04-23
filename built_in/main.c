#include "../minishell.h"
void    ft_export(char **env, int i);

int	ft_strcmp(char *line, char *str)
{
	int	i;

	i = 0;
	while (line[i] && str[i])
	{
		if (line[i] != str[i])
			return (0);
		i++;
	}
	if (line[i] || str[i])
		return (0);
	return (1);
}

void	handler(int sig)
{
	(void)sig;
	write (1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	// printf("\nprompt2>$ ");
}

void	ft_exit(int ext_st)
{
	printf("exit\n");
	exit (ext_st);
}

void	ft_cat(void)
{
	int id;

	id = fork();
	if (id == -1)
		write (2, "Error\n", 6);
	if (!id)
	{
		char *arg[] = {"cat", NULL};
		execve("/usr/bin/cat", arg, NULL);
		printf("Failed\n");
		exit (5);
	}
	waitpid(id, NULL, 0);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	char	cwd[1024];
	char	*cmd;
	int	i;

	if (!getcwd(cwd, 1024))
		return (1);
	signal(SIGINT, handler);
	while (1)
	{
		cmd = readline("prompt>$ ");
		if (!cmd)
			ft_exit(0);
		if (ft_strcmp(cmd, "pwd"))
			printf("%s\n", cwd);
		else if (ft_strcmp(cmd, "exit"))
		{
			free (cwd);
			free (cmd);
			ft_exit(0);
		}
		else if (ft_strcmp(cmd, "export"))
		{
			i = 0;
			while (env[i])
				i++;
			ft_export(env, i);
		}
		else if (ft_strcmp(cmd, "cat"))
			ft_cat();
		free (cmd);
	}
	free (cwd);
	return (0);
}
