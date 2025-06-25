/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 09:48:46 by mfahmi            #+#    #+#             */
/*   Updated: 2025/06/20 10:32:52 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s, t_free_type place)
{
	char	*d;
	int		i;
	int		length;

	if (!s)
		return (NULL);
	length = ft_strlen(s);
	i = 0;
	d = ft_malloc(length + 1, place, FREE);
	while (i <= length)
	{
		d[i] = s[i];
		i++;
	}
	return (d);
}
