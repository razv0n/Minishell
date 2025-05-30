/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:14:04 by mfahmi            #+#    #+#             */
/*   Updated: 2025/05/12 14:18:05 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

t_list	*ft_lstnew_d(void *content)
{
	t_list	*newnode;

	newnode = malloc(sizeof(t_list));
	if (!newnode)
		return (NULL);
	newnode->content = content;
	newnode->next = NULL;
	newnode->prev = NULL;
	return (newnode);
}

t_ptr	*ft_lstnew_ptr(void *content)
{
	t_ptr	*newnode;

	newnode = malloc(sizeof(t_list));
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

void remove_the_null(t_list **head)
{
	t_list *help;
	t_list *tmp;

	help = *head;
	while (help)
	{
		if (!help->content)
		{
			tmp = help->next;
			remove_node(head, help);
			help = tmp;
		}
		else
			help = help->next;
	}
}

/*int main()
{
	t_list *head = NULL;
	void *content = (char *)"hello";
	t_list *newnode = ft_lstnew(content);
	head = newnode;

		printf("%s",(char *)newnode->content);
}*/
