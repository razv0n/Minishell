/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 10:08:47 by mfahmi            #+#    #+#             */
/*   Updated: 2025/05/10 10:37:13 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst != NULL)
	{
		f(lst->content);
		lst = lst->next;
	}
}
/*void    f(void *content)
{
        char *con = (char *)content;
        for(int i = 0 ; i < sizeof(con) ; i++)
                con[i] >= 'a' && con[i] <= 'z'? con[i] -= 32 : con[i];
}
int main ()
{
	t_list *head = NULL;

	t_list *lk_1 =ft_mallocsizeof(t_list));
	head = lk_1;
	lk_1->next = NULL;
	lk_1->content = ft_strdup("hello");
	ft_lstiter(lk_1,f);
	printf ("%s",(char *)lk_1->content);
}*/
