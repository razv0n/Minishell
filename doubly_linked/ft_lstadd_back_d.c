/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_d.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:24:57 by mfahmi            #+#    #+#             */
/*   Updated: 2025/05/12 14:22:05 by mfahmi           ###   ########.fr       */
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

void	ft_lstadd_back_ptr(t_ptr **start, t_ptr *new)
{
	t_ptr	*help;

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
}

void	ft_lstclear_d(t_list **lst)
{
	t_list	*help;

	if (!lst || !*lst)
		return ;
	while (*lst != NULL)
	{
		free((*lst)->content);
		help = (*lst)->next;
		free (*lst);
		*lst = help;
	}
	*lst = NULL;
}

void	ft_lstclear_not(t_list **lst)
{
	t_list	*help;

	if (!lst || !*lst)
		return ;
	while (*lst != NULL)
	{
		help = (*lst)->next;
		free (*lst);
		*lst = help;
	}
}

void	ft_lstclear_ptr(t_ptr **lst)
{
	t_ptr	*help;

	if (!lst || !*lst)
		return ;
	while (*lst != NULL)
	{
		help = (*lst)->next;
		free (*lst);
		*lst = help;
	}
	*lst = NULL;
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
