/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 09:48:46 by mfahmi            #+#    #+#             */
/*   Updated: 2025/05/08 16:42:10 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*d;
	int		i;
	int		length;

	if (!s)
		return (NULL);
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
