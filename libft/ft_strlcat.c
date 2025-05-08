/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:24:10 by mfahmi            #+#    #+#             */
/*   Updated: 2024/11/06 17:57:58 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	ids;
	size_t	isr;
	size_t	tot;

	isr = ft_strlen(src);
	if (!dst && !size)
		return (isr);
	ids = ft_strlen((const char *)dst);
	i = 0;
	if (size <= ids)
	{
		tot = size + isr;
		return (tot);
	}
	else
		tot = isr + ids;
	while (i + ids < size - 1 && src[i])
	{
		dst[ids + i] = src[i];
		i++;
	}
	dst[ids + i] = '\0';
	return (tot);
}
/*int main ()
{
	char dest[] = "waaa hello wa ha";
	char src[] = "halloz al grga3";
	printf("%ld\n", ft_strlcat(dest,src,18));
	printf("%s", dest);
}*/
