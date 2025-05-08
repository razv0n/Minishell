/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 09:48:46 by mfahmi            #+#    #+#             */
/*   Updated: 2024/11/04 21:13:21 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*d;
	int		i;
	int		length;

	length = ft_strlen(s);
	i = 0;
	d = malloc (length + 1);
	if (!d)
		return (NULL);
	while (i <= length)
	{
		d[i] = s[i];
		i++;
	}
	return (d);
}
