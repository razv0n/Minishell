#include "../minishell.h"

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
	printf("\nprompt>$ ");
}

void	ft_exit(int ext_st)
{
	printf("exit\n");
	exit (ext_st);
}

int main(void)
{
	char	*cwd;
	char	*cmd;

	cwd = NULL;
	cmd = NULL;
	cwd = getcwd(cwd, 1024);
	if (!cwd)
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
		free (cmd);
	}
	free (cwd);
	return (0);
}
