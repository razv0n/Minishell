/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:14:04 by mfahmi            #+#    #+#             */
/*   Updated: 2025/06/01 10:53:12 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

t_list	*ft_lstnew_d(void *content, t_free_type place)
{
	t_list	*newnode;

	newnode = ft_malloc(sizeof(t_list), place, F_STRUCT);
	newnode->content = content;
	newnode->next = NULL;
	newnode->prev = NULL;
	return (newnode);
}

t_ptr	*ft_lstnew_ptr(void *content)
{
	t_ptr	*newnode;

	newnode = malloc(sizeof(t_ptr));
	if (!newnode)
		return (NULL);
	newnode->content = content;
	newnode->next = NULL;
	return (newnode);
}

void remove_node (t_list **head, t_list *remove)
{
    if	(!*head || !remove|| !head)
		return ;
    if (remove->prev)
    {
        remove->prev->next = remove->next;
		if (remove->next)
        	remove->next->prev = remove->prev;
    }
    else
    {
        *head = (*head)->next;
		if (*head)
        	(*head)->prev = NULL;
    }
    ft_lstdelone(remove, free);
}

/*int main()
{
	t_list *head = NULL;
	void *content = (char *)"hello";
	t_list *newnode = ft_lstnew(content);
	head = newnode;

		printf("%s",(char *)newnode->content);
}*/
