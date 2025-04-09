#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

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

int main(void)
{
	char	*cwd;
	char	*cmd;
	// size_t	size;

	cwd = NULL;
	cmd = NULL;
	// size = 1024;
	cwd = getcwd(cwd, 100);
	while (1)
	{
		cmd = readline("prompt>$ ");
		if (!cwd || !cmd)
			return (1);
		if (ft_strcmp(cmd, "pwd"))
		{
			printf("prompt>$ %s", cwd);
			free (cmd);
			break;
		}
		free (cmd);
	}
	free (cwd);
	return (0);
}
