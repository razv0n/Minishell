/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syscall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 17:18:46 by mfahmi            #+#    #+#             */
/*   Updated: 2025/06/27 21:28:39 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

e_sys_err	ft_close(int fd)
{
    t_ptr   *node;

        if (close(fd) == -1)
			return (SYS_FAIL);
        node = where_is_fd(*(return_ptr()), fd);
        if (node)
            *((int *)node->content) = -2;// -2 mean fd is all ready closed this help me for close the fd if it all read close dont wory it wont closed
	return (SYS_SUCCESS);
}

e_sys_err	ft_pipe(int pip[2]) // if the pip fail  it should retrun an fail in exit
{
	int		*ptr_fd;
	int		*ptr_fd2;
	
	if (pipe(pip) == -1)
		return (SYS_FAIL);
	ptr_fd = ft_malloc(sizeof(int), SECOUND_P, CLOSE);
	ptr_fd2 = ft_malloc(sizeof(int), SECOUND_P, CLOSE);
	*ptr_fd = pip[0];
	*ptr_fd2 = pip[1];
	return (SYS_SUCCESS);
}


int		ft_dupX(int	fd1, int fd2, bool is_dup2)
{
	int		*ptr_fd;

	if (is_dup2)
	{
		if (dup2(fd1, fd2) == -1)
			return (SYS_FAIL);
	}
	else
	{
		fd1 = dup(fd1);
		if (fd1 == -1)
			return (SYS_FAIL);
		ptr_fd = ft_malloc(sizeof(int), SECOUND_P, CLOSE);
		*ptr_fd = fd1;
	}
	return (fd1);
}

int    ft_open(char *str, int flag, int permi)
{
    int fd;
    int *ptr_fd;

    if ((flag & O_CREAT) == O_CREAT)
        fd = open(str, flag, permi);
    else
        fd = open(str, flag);
    if (fd == -1)
		return (SYS_FAIL);
	ptr_fd = ft_malloc(sizeof(int), SECOUND_P, CLOSE);
	*ptr_fd = fd;
    return (fd);
}