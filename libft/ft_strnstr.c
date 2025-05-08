/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:08:17 by mfahmi            #+#    #+#             */
/*   Updated: 2024/11/13 21:44:04 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	length;

	if (!len && !str)
		return (NULL);
	if (!*to_find)
		return ((char *)str);
	length = ft_strlen(to_find);
	i = 0;
	while (str[i] && i < len)
	{
		j = 0;
		while (str[i + j] == to_find[j] && to_find[j] && (j + i) < len)
			j++;
		if (j == length)
			return ((char *)(str + i));
		i++;
	}
	return (NULL);
}
