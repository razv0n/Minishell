/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:26:57 by yezzemry          #+#    #+#             */
/*   Updated: 2025/05/08 21:49:51 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void	herdoc(char *str , t_info *info)
{
    char    *line;
    pid_t    id;

	if (info->ext != 130)
	{
		id = fork();
		if (id == -1 || dup2(info->utils->fd_in, 0) == -1 || pipe(info->utils->pi) == -1)
			exit(1);
		else if (id == 0)
		{
			signal(SIGINT, SIG_DFL);
			while (1)
			{
				line = readline("> ");
				if (!line || ft_strcmp(line, str) == 1)
				{
					free(line);
					break ;
				}
				if (line[0])
					add_history(line);
				ft_putstr_fd(line, info->utils->pi[1]);
				ft_putstr_fd("\n", info->utils->pi[1]);
				free(line);
			}
			close(info->utils->pi[0]);
			close(info->utils->pi[1]);
			// ft_free(info, FR_CHILD);
			exit(1);
		}
		wait(&info->ext);
		// printf("%d\n", info->ext);
		exit_status(info);
		// printf("%d\n", info->ext);
		if (dup2(info->utils->pi[0], 0) == -1) // fd to stdin
			perror("Minishell");
		close (info->utils->pi[0]); // !handle the >>'d'
		close (info->utils->pi[1]);
	}
}

void	redirection(char *str, int cdt, t_info *info)
{
	int	fd;

	if (cdt == APPEND)
	{
		fd = open(str, O_CREAT | O_APPEND | O_RDWR, 0766);
		if (fd == -1 || dup2(fd, 1) == -1)
			exit(5);
		close (fd);
	}
	else if (cdt == REDIRECT_IN)
	{
		if (access(str, F_OK) == -1)
			printf("minishell: No such file or directory %s\n", str);
		else
		{
			fd = open(str, O_RDONLY, 0766);
			if (fd == -1 || dup2(fd, 0) == -1)
				exit(6);
			close (fd);
		}
	}
	else if (cdt == HEREDOC)
		herdoc(str, info);
	else if (cdt == REDIRECT_OUT)
	{
		fd = open(str, O_CREAT | O_TRUNC | O_RDWR, 0766);
		if (fd == -1 || dup2(fd, 1) == -1)
			exit(7);
		close (fd);
	}
}
