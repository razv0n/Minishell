/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 10:39:45 by mfahmi            #+#    #+#             */
/*   Updated: 2024/11/09 22:20:12 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*newnode;
	void	*content;

	if (!lst || !f || !del)
		return (NULL);
	head = NULL;
	newnode = NULL;
	while (lst != NULL)
	{
		content = f(lst->content);
		newnode = ft_lstnew(content);
		if (!newnode)
		{
			ft_lstclear(&newnode, del);
		}
		ft_lstadd_back(&head, newnode);
		lst = lst->next;
	}
	return (head);
}
/*void *f(void *p)
{
	char	*k;

		k = (char *)p;
		for (int i = 0 ; i < k[i] ; i++)
				k[i] >= 'a' && k[i] <= 'z' ? k[i] -= 32: k[i];
		return (p);
}
void del (void *content)
{
		free(content);
}
int main ()
{
	t_list    *head = NULL;
	t_list    *lk, *lk_2, *lk_3;
	lk = malloc (sizeof(t_list));
	lk_2 = malloc (sizeof(t_list));
	head = lk;
	lk->next = lk_2;
	lk_2->next = NULL;
	//lk_3 = malloc (sizeof(t_list));
	lk->content = ft_strdup("hello");
	lk_2->content = ft_strdup("lol");
	t_list *head_1 = ft_lstmap(head, f, del);
}*/
