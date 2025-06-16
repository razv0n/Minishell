/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:48:12 by mfahmi            #+#    #+#             */
/*   Updated: 2024/11/07 18:04:42 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*help;
	int		count;

	if (!lst)
		return (0);
	help = lst;
	count = 0;
	while (help != NULL)
	{
		count++;
		help = help->next;
	}
	return (count);
}
/*int main ()
{
	t_list *head = NULL;
	t_list *nw , *nww;
	nw = malloc (sizeof(t_list));
	nww = malloc (sizeof(t_list));
	head = nw;
	nw->next = nww;
	nww->next = NULL;
	printf ("%d", ft_lstsize(nw));
}*/
