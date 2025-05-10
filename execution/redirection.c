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

void	redirection(char *str, int cdt)
{
	int	fd;

	if (cdt == APPEND)
	{
		fd = open(str, O_CREAT | O_APPEND | O_RDWR);
		if (dup2(fd, 1) == -1)
			exit(5);
		close (fd);
	}
	else if (cdt == REDIRECT_IN)
	{
		if (access(str, F_OK) == -1)
			printf("minishell: No such file or directory %s\n", str);
		else
		{
			fd = open(str, O_RDONLY);
			if (dup2(fd, 0) == -1)
				exit(6);
			close (fd);
		}
	}
	else if (cdt == REDIRECT_OUT)
	{
		fd = open(str, O_CREAT | O_TRUNC | O_RDWR);
		if (dup2(fd, 1) == -1)
			exit(7);
		close (fd);
	}
}
