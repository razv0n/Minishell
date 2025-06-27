/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 15:07:11 by mfahmi            #+#    #+#             */
/*   Updated: 2025/06/26 11:03:21 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2, t_free_type place)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!s2)
		return (ft_strdup(s1, place));
	if (!s1)
		return (ft_strdup(s2, place));
	i = 0;
	j = 0;
	str = ft_malloc(ft_strlen(s1) + ft_strlen(s2) + 1, place, FREE);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	return (str[i] = '\0', str);
}
/*
int main ()
{
	printf("%s",ft_strjoin("hello ","world!"));
}*/
