/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redr_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 12:17:10 by mfahmi            #+#    #+#             */
/*   Updated: 2025/06/13 12:21:39 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void	rdr_in(char *str, t_info *info)
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
        {
            if (fd != -1)
                close (fd);
			ft_free_all(NORMAL, 4); // error in file descriptor
        }
		close(fd);
	}
}

void	rdr_herdoc(t_info *info)
{
	static int i;
	int fd;
	
	fd = open(info->path_name[i], O_RDWR, 0766);
	if (fd == -1 || dup2(fd, 0) == -1)
    {
        if (fd != -1)
            close (fd);
		ft_free_all(NORMAL, 4);
    }
	if (++i >= info->count_herdoc)
		i = 0;
	close(fd);
}

void	rdr_append(char *str)
{
	int fd;

	fd = open(str, O_CREAT | O_APPEND | O_RDWR, 0766);
	if (fd == -1 || dup2(fd, 1) == -1)
	{
		if (fd != -1)
			close(fd);
		ft_free_all(NORMAL, 4); // error in file descriptor
	}
	close(fd);
}

void	rdr_out(char	*str)
{
	int	fd;
	
	fd = open(str, O_CREAT | O_TRUNC | O_RDWR, 0766);
	if (fd == -1 || dup2(fd, 1) == -1)
	{ 
		if (fd != -1)
			close(fd);
	    ft_free_all(NORMAL, 4);// error in file descriptor
	}
	close(fd);
}
