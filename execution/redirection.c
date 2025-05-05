/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yezzemry <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:26:57 by yezzemry          #+#    #+#             */
/*   Updated: 2025/04/24 11:27:12 by yezzemry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void	redirection(char *str, int cdt)
{
	int	fd;

	if (cdt == APPEND)
	{
		fd = open(str, O_CREAT | O_APPEND | O_WRONLY);
		if (dup2(fd, 1) == -1)
			exit(5);
		close (fd);
	}
	else if (cdt == REDIRECT_IN)
	{
		fd = open(str, O_RDONLY);
		if (dup2(fd, 0) == -1)
			exit(6);
		close (fd);
	}
	else if (cdt == REDIRECT_OUT)
	{
		fd = open(str, O_CREAT | O_TRUNC | O_WRONLY);
		if (dup2(fd, 1) == -1)
			exit(7);
		close (fd);
	}
}
