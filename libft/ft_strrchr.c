/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:56:05 by mfahmi            #+#    #+#             */
/*   Updated: 2024/11/01 10:16:08 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	i;

	i = (int)ft_strlen(str);
	if (!c)
		return ((char *)(str + i));
	i--;
	while (i >= 0)
	{
		if (str[i] == c)
			return ((char *)(str + i));
		i--;
	}
	return (NULL);
}
