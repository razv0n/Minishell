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
	return (1);
}

int main(void)
{
	char	*cwd;
	char	*cmd;
	size_t	size;

	cwd = NULL;
	cmd = NULL;
	size = 1024;
	cmd = readline("prompt>$ ");
	cwd = getcwd(cwd, size);
	if (!cwd || !cmd)
		return (1);
	if (ft_strcmp(cmd, "pwd"))
		printf("\nprompt>$ %s", cwd);
	free (cmd);
	return (0);
}
