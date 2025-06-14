/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 11:02:50 by mfahmi            #+#    #+#             */
/*   Updated: 2025/06/13 17:47:15 by mfahmi           ###   ########.fr       */
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
		substr = ft_malloc(len + 1, SECOUND_P);
		if (!substr)
			return (NULL);
	}
	else
		return (ft_strdup("", SECOUND_P));
	return (ft_cpyy(len, start, s, substr));
}
/*int	main ()
{
	printf("%s",ft_substr("", 2, 4)); // the start is the index
}*/
