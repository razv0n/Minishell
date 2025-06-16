/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:14:04 by mfahmi            #+#    #+#             */
/*   Updated: 2025/06/14 15:18:44 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

t_list	*ft_lstnew_d(void *content, t_free_type place)
{
	t_list	*newnode;

	newnode = ft_malloc(sizeof(t_list), place);
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
		ft_free_all(ERR_MALLOC, 3);
	newnode->content = content;
	newnode->next = NULL;
	return (newnode);
}

void	remove_node_doubly(t_list **head, t_list *remove)
{
	if (!*head || !remove || !head)
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
	// ft_lstdelone(remove, free);
}

void	remove_node_single(t_ptr **head, t_ptr *remove)
{
	t_ptr	*help;
	t_ptr	*prev;

	help = *head;
	prev = NULL;
	if (!*head || !remove || !head)
		return ;
	while (help != remove)
	{
		prev = help;
		help = help->next;
	}
	if (*head == remove)
		*head = (*head)->next;
	else
		prev->next = remove->next;
	free(remove->content);
	free(remove);
}

/*int main()
{
	t_list *head = NULL;
	void *content = (char *)"hello";
	t_list *newnode = ft_lstnew(content);
	head = newnode;

		printf("%s",(char *)newnode->content);
}*/
