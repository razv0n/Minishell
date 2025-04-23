/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_d.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:08:26 by mfahmi            #+#    #+#             */
/*   Updated: 2025/04/23 11:59:49 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void	ft_lstadd_front_d(t_list **lst, t_list *new)
{
	if (!new || !lst)
		return ;
	new->next = *lst;
    new->prev = NULL;
    (*lst)->prev = new;
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
