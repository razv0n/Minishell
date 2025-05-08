/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 09:09:38 by mfahmi            #+#    #+#             */
/*   Updated: 2024/10/28 21:49:43 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nitems, size_t size)
{
	void	*ptr;
	size_t	i;

	i = 0;
	ptr = malloc (nitems * size);
	if (!ptr)
		return (NULL);
	while (i < (nitems * size))
	{
		((char *)ptr)[i] = 0;
		i++;
	}
	return (ptr);
}
