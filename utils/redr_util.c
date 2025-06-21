/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redr_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 12:17:10 by mfahmi            #+#    #+#             */
/*   Updated: 2025/06/19 16:57:52 by mfahmi           ###   ########.fr       */
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
		fd = ft_open(str, O_RDONLY, 0);
		ft_dupX(fd, 0, true);
		ft_close(fd);
	}
}

void	rdr_herdoc(t_info *info)
{
	static int	i;
	int			fd;

	fd = ft_open(info->path_name[i], O_RDWR, 0);
	ft_dupX(fd, 0, true);
	if (++i >= info->count_herdoc)
		i = 0;
	ft_close(fd);
}

void	rdr_append(char *str)
{
	int	fd;

	fd = ft_open(str, O_CREAT | O_APPEND | O_RDWR, 0766);
	ft_dupX(fd, 1, true);
	ft_close(fd);
}

void	rdr_out(char *str)
{
	int	fd;

	fd = ft_open(str, O_CREAT | O_TRUNC | O_RDWR, 0766);
	ft_dupX(fd, 1, true);
	ft_close(fd);
}
