/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:08:26 by mfahmi            #+#    #+#             */
/*   Updated: 2024/11/09 18:13:25 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!new || !lst)
		return ;
	new->next = *lst;
	*lst = new;
}
/*int main()
{
    t_list *head = NULL;
    t_list *nww = malloc (sizeof(t_list));
    t_list *nw = malloc (sizeof(t_list));
    nw->content = (char *)"hello";
    ft_lstadd_front(&head, nw);
    nww->content = (char *)"hello";
    ft_lstadd_front(&head, nww);
}*/
