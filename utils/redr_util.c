/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redr_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 12:17:10 by mfahmi            #+#    #+#             */
/*   Updated: 2025/07/13 18:35:48 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

t_sys_err	rdr_in(char *str)
{
	int	fd;

	fd = ft_open(str, O_RDONLY, 0);
	if (fd == SYS_FAIL || ft_dupx(fd, 0, true) == SYS_FAIL)
		return (SYS_FAIL);
	ft_close(fd);
	return (SYS_SUCCESS);
}

t_sys_err	rdr_herdoc(t_info *info)
{
	static int	i;
	int			fd;

	fd = ft_open(info->path_name[i], O_RDWR, 0);
	if (fd == SYS_FAIL || ft_dupx(fd, 0, true) == SYS_FAIL)
		return (SYS_FAIL);
	if (++i >= info->count_herdoc)
		i = 0;
	ft_close(fd);
	return (SYS_SUCCESS);
}

t_sys_err	rdr_append(char *str)
{
	int	fd;

	fd = ft_open(str, O_CREAT | O_APPEND | O_RDWR, 0644);
	if (fd == SYS_FAIL || ft_dupx(fd, 1, true) == SYS_FAIL)
		return (SYS_FAIL);
	ft_close(fd);
	return (SYS_SUCCESS);
}

t_sys_err	rdr_out(char *str)
{
	int	fd;

	fd = ft_open(str, O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (fd == SYS_FAIL || ft_dupx(fd, 1, true) == SYS_FAIL)
		return (SYS_FAIL);
	ft_close(fd);
	return (SYS_SUCCESS);
}

void	help_norm(char *str, t_list *head)
{
	if (check_quotes(str[0]))
		remove_quotes(&str, head->next);
}
