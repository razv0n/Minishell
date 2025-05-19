/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:38:05 by mfahmi            #+#    #+#             */
/*   Updated: 2025/05/13 15:49:29 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

<<<<<<< HEAD
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
=======
void herdoc(char *str , t_u *utils)
{
	char	*line;

	if (dup2(utils->fd_in, 0) || pipe(utils->pi) == -1)
		perror("Minishell");
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, str) == 1)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, utils->pi[1]);
		write(utils->pi[1], "\n", 1);
		free(line);
	}
	close(utils->pi[1]);
	if (dup2(utils->pi[0], 0) == -1) // fd to stdin
		perror("Minishell");
	close (utils->pi[0]);
	// utils->str_heredoc = str;
}

void	redirection(char *str, int cdt, t_u *utils)
>>>>>>> 1832faa0f55e6cd6d9b059647537ff51e67a5ba2
{
	int	fd;

	if (cdt == APPEND)
	{
<<<<<<< HEAD
		fd = open(str, O_CREAT | O_APPEND | O_RDWR, 0766);
		if (fd == -1 || dup2(fd, 1) == -1)
			exit(5);
=======
		fd = open(str, O_CREAT | O_APPEND | O_RDWR, 0777);
		if (dup2(fd, 1) == -1 || fd == -1)
			perror("Minishell");			
>>>>>>> 1832faa0f55e6cd6d9b059647537ff51e67a5ba2
		close (fd);
	}
	else if (cdt == REDIRECT_IN)
	{
		if (access(str, F_OK) == -1)
			ft_putstr_fd("minishell: No such file or directory\n", 2); // u should specify the name of the file
		else
		{
<<<<<<< HEAD
			fd = open(str, O_RDONLY, 0766);
			if (fd == -1 || dup2(fd, 0) == -1)
				exit(6);
=======
			fd = open(str, O_RDONLY, 0777);
			if (dup2(fd, 0) == -1 || fd == -1)
				perror("Minishell");
>>>>>>> 1832faa0f55e6cd6d9b059647537ff51e67a5ba2
			close (fd);
		}
	}
	else if (cdt == HEREDOC)
<<<<<<< HEAD
		herdoc(str, info);
	else if (cdt == REDIRECT_OUT)
	{
		fd = open(str, O_CREAT | O_TRUNC | O_RDWR, 0766);
		if (fd == -1 || dup2(fd, 1) == -1)
			exit(7);
=======
		herdoc(str, utils);
	else if (cdt == REDIRECT_OUT)
	{
		fd = open(str, O_CREAT | O_TRUNC | O_RDWR, 0777);
		if (dup2(fd, 1) == -1 || fd == -1)
			perror("Minishell");
>>>>>>> 1832faa0f55e6cd6d9b059647537ff51e67a5ba2
		close (fd);
	}
}