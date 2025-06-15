/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 20:57:20 by mfahmi            #+#    #+#             */
/*   Updated: 2024/10/31 18:42:22 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	*pstr;

	if (!n)
		return (NULL);
	pstr = (unsigned char *)str;
	i = 0;
	while (i < n)
	{
		if (pstr[i] == (unsigned char)c)
			return ((void *)(str + i));
		i++;
	}
	return (NULL);
}
/*int main ()
{
	const char str[] = "this is a test";
	ft_memchr(str, 'i', sizeof(str));cod
	printf("%s", str);
}*/
