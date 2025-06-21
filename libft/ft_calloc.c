/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 09:09:38 by mfahmi            #+#    #+#             */
/*   Updated: 2025/06/20 10:32:08 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nitems, size_t size)
{
	void	*ptr;
	size_t	i;

	i = 0;
	ptr = ft_malloc(nitems * size, SECOUND_P, FREE);
	while (i < (nitems * size))
	{
		((char *)ptr)[i] = 0;
		i++;
	}
	return (ptr);
}
