/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:32:59 by mfahmi            #+#    #+#             */
/*   Updated: 2025/06/17 14:40:17 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void	init_info(t_info *info)
{
	info->head_cmd = NULL;
	info->joined = NULL;
	info->fd_in = dup(0);
	info->fd_out = dup(1);
	if (info->fd_in == -1 || info->fd_out == -1)
		ft_free_all(NORMAL, 4);
}

t_ptr	**return_ptr(void)
{
	static t_ptr	*head;

	return (&head);
}

void	add_ptr(void *ptr, t_ptr **head, t_free_type place)
{
	t_ptr	*new_node;

	new_node = ft_lstnew_ptr(ptr);
	new_node->place = place;
	if (!new_node)
		ft_free_all(ERR_MALLOC, 3);
	ft_lstadd_back_ptr(head, new_node);
}

void	*ft_malloc(size_t size, t_free_type place)
{
	void	*ptr;
	t_ptr	**head;

	head = return_ptr();
	ptr = malloc(size);
	if (!ptr)
		ft_free_all(ERR_MALLOC, 3);
	add_ptr(ptr, head, place);
	return (ptr);
}
