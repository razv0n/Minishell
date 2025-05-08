/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 10:42:00 by mfahmi            #+#    #+#             */
/*   Updated: 2024/11/11 10:50:58 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*ps1;
	const unsigned char	*ps2;

	if (!n)
		return (0);
	i = 0;
	ps1 = (const unsigned char *)s1;
	ps2 = (const unsigned char *)s2;
	while (i < n - 1 && ps1[i] == ps2[i])
	{
		i++;
	}
	return ((unsigned char)ps1[i] - (unsigned char)ps2[i]);
}
