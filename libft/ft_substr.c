/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 11:02:50 by mfahmi            #+#    #+#             */
/*   Updated: 2024/11/06 17:44:55 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_cpyy(size_t len,
		unsigned int start, char const *s, char *substr)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		substr[i] = s[start];
		start++;
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	lenght;

	if (!s)
		return (NULL);
	lenght = ft_strlen(s);
	if (start <= lenght)
	{
		if (lenght - start < len)
			len = lenght - start;
		substr = malloc(len + 1);
		if (!substr)
			return (NULL);
	}
	else
		return (ft_strdup(""));
	return (ft_cpyy(len, start, s, substr));
}
/*int	main ()
{
	printf("%s",ft_substr("", 2, 4)); // the start is the index
}*/
