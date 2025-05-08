/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:05:45 by mfahmi            #+#    #+#             */
/*   Updated: 2024/11/09 23:09:46 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*help;

	if (!lst)
		return (NULL);
	help = lst;
	while (help->next != NULL)
		help = help->next;
	return (help);
}
/*int main ()
{
	t_list	*head = NULL;
	t_list	*lk, *lk_2;
	head = lk;
	lk->next = lk_2;
	lk_2->next = NULL;
	t_list *test = ft_lstlast(lk);
       //if (test == lk)
       	//	printf ("done");
	//else
	 	//printf ("faild");	
}*/
