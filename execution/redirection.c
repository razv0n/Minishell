/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:38:05 by mfahmi            #+#    #+#             */
/*   Updated: 2025/05/19 17:30:20 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void	herdoc(char *str , t_info *info)
{
	char	*line;
	pid_t	id;
	int	pip[2];

	if (info->ext != 130)
	{
		if (pipe(pip) == -1)
			exit(1);
		id = fork();
		if (id == -1 || dup2(info->utils->fd_in, 0) == -1
			|| dup2(info->utils->fd_out, 1) == -1)
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
				ft_putstr_fd(line, pip[1]);
				ft_putstr_fd("\n", pip[1]);
				free(line);
			}
			close(pip[0]);
			close(pip[1]);
			// ft_free(info, FR_CHILD);
			exit(1);
		}
		wait(&info->ext);
		exit_status(info);
		if (dup2(pip[0], 0) == -1) // fd to stdin
			perror("Minishell");
		close (pip[0]); // !handle the >>'d'
		close (pip[1]);
	}
}

int	rdr_in(char *str, t_info *info)
{
	int	fd;

	if (access(str, F_OK) == -1)
	{
		ft_putstr_fd("minshell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		info->utils->fail = -1;
	}
	else
	{
		fd = open(str, O_RDONLY, 0766);
		if (fd == -1 || dup2(fd, 0) == -1)
			exit(1); // error in file descriptor
		close (fd);
	}
}

void	redirection(char *str, int cdt, t_info *info)
{
	int	fd;

	if (cdt == APPEND)
	{
		fd = open(str, O_CREAT | O_APPEND | O_RDWR, 0766);
		if (fd == -1 || dup2(fd, 1) == -1)
			exit(1); // error in file descriptor
		close (fd);
	}
	else if (cdt == REDIRECT_IN)
		rdr_in(str, info);
	else if (cdt == HEREDOC)
		herdoc(str, info);
	else if (cdt == REDIRECT_OUT)
	{
		fd = open(str, O_CREAT | O_TRUNC | O_RDWR, 0766);
		if (fd == -1 || dup2(fd, 1) == -1)
			exit(1); // error in file descriptor
		close (fd);
	}
}

// if (access(str, F_OK) == -1)
// {
// 	ft_putstr_fd("minshell: ", 2);
// 	ft_putstr_fd(str, 2);
// 	ft_putstr_fd(": No such file or directory\n", 2);
// 	info->utils->fail = -1;
// }
// else
// {
// 	fd = open(str, O_RDONLY, 0766);
// 	if (fd == -1 || dup2(fd, 0) == -1)
// 		exit(1); // error in file descriptor
// 	close (fd);
// }