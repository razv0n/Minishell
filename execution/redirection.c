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
{
	int	fd;

	if (cdt == APPEND)
	{
		fd = open(str, O_CREAT | O_APPEND | O_RDWR, 0777);
		if (dup2(fd, 1) == -1 || fd == -1)
			perror("Minishell");			
		close (fd);
	}
	else if (cdt == REDIRECT_IN)
	{
		if (access(str, F_OK) == -1)
			ft_putstr_fd("minishell: No such file or directory\n", 2); // u should specify the name of the file
		else
		{
			fd = open(str, O_RDONLY, 0777);
			if (dup2(fd, 0) == -1 || fd == -1)
				perror("Minishell");
			close (fd);
		}
	}
	else if (cdt == HEREDOC)
		herdoc(str, utils);
	else if (cdt == REDIRECT_OUT)
	{
		fd = open(str, O_CREAT | O_TRUNC | O_RDWR, 0777);
		if (dup2(fd, 1) == -1 || fd == -1)
			perror("Minishell");
		close (fd);
	}
}