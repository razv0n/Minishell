/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 11:15:06 by mfahmi            #+#    #+#             */
/*   Updated: 2024/11/09 21:51:46 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*help;

	if (!lst || !del || !*lst)
		return ;
	while (*lst != NULL)
	{
		del((*lst)->content);
		help = (*lst)->next;
		free (*lst);
		*lst = help;
	}
}
/*void del (void *content)
{
        free(content);
}
int main()
{
        t_list *head = NULL;
        t_list *lk_1, *lk_2, *lk_3;
        lk_1 = malloc(sizeof(t_list));
        lk_2 = malloc(sizeof(t_list));
        lk_3 = malloc(sizeof(t_list));
        head = lk_1;
        lk_1->next = lk_2;
        lk_2->next = lk_3;
        lk_3->next = NULL;
        lk_1->content = ft_strdup("hello");
	lk_2->content = ft_strdup("gi");
	lk_3->content = ft_strdup("lol");
        ft_lstdelone(&lk_1 ,del);
}*/
