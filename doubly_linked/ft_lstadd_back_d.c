/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_d.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:24:57 by mfahmi            #+#    #+#             */
/*   Updated: 2025/04/23 12:00:09 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void	ft_lstadd_back_d(t_list **start, t_list *new)
{
	t_list	*help;

	if (!new || !start)
		return ;
	if (*start == NULL)
	{
		*start = new;
		return ;
	}
	help = *start;
	while (help->next != NULL)
		help = help->next;
	help->next = new;
    new->prev = help;
}
/*int main ()
{
    t_list    *head = NULL;
    t_list    *lk, *lk_2, *lk_3;
    lk = malloc (sizeof(t_list));
     lk_2 = malloc (sizeof(t_list));
    head = lk;
    lk->next = lk_2;
    lk_2->next = NULL;
    lk_3 = malloc (sizeof(t_list));
    t_list *test = ft_lstlast(&head, lk_3);
       //if (test == lk)
           //    printf ("done");
    //else
         //printf ("faild");    
}*/
