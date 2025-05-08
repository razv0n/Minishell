/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 21:38:07 by mfahmi            #+#    #+#             */
/*   Updated: 2024/10/31 12:54:56 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
// int main ()
// {
// 	int fd = open("file.txt", O_RDONLY | O_CREAT, 0644);
// 	ft_putchar_fd(c, fd);
// 	printf("%d", fd);
// 	close(fd);// sajdas
// }
// dlashdasldas
//dkasdgasjs