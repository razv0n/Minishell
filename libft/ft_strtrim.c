/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 15:41:03 by mfahmi            #+#    #+#             */
/*   Updated: 2024/11/01 18:32:35 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_find(const char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	ft_find_rev(const char *str, char c)
{
	int	i;

	i = (int) ft_strlen(str) - 1;
	while (i >= 0)
	{
		if (str[i] == c)
			return (1);
		i--;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	char	*str;
	int		j;
	size_t	in;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	in = 0;
	j = (int)ft_strlen(s1) - 1;
	while (ft_find(set, s1[i]) && s1[i])
		i++;
	while (ft_find_rev(set, s1[j]) && s1[i])
		j--;
	str = malloc (sizeof(char) * (j - i + 2));
	if (!str)
		return (NULL);
	while (i <= j)
		str[in++] = s1[i++];
	str[in] = '\0';
	return (str);
}
/*#include <string.h>
int main ()
{
	//char *result = ft_strtrim("", "ef");
    printf("%s",ft_strtrim("   ", " "));
}*/
