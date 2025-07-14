/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:32:59 by mfahmi            #+#    #+#             */
/*   Updated: 2025/07/14 17:51:52 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

t_sys_err	init_info(t_info *info)
{
	info->head_cmd = NULL;
	info->joined = NULL;
	info->fd_in = ft_dupx(0, -1, false);
	info->fd_out = ft_dupx(1, -1, false);
	if (info->fd_in == -1 || info->fd_out == -1)
		return (fail_sys_call(info, SYS_FAIL));
	info->sigint_herdoc = false;
	return (SYS_SUCCESS);
}

t_ptr	**return_ptr(void)
{
	static t_ptr	*head;

	return (&head);
}

void	add_ptr(void *ptr, t_ptr **head, t_free_type place, t_free_type type)
{
	t_ptr	*new_node;

	new_node = ft_lstnew_ptr(ptr);
	if (!new_node)
		ft_free_all(ERR_MALLOC, 1);
	new_node->place = place;
	new_node->type = type;
	ft_lstadd_back_ptr(head, new_node);
}

void	*ft_malloc(size_t size, t_free_type place, t_free_type type)
{
	void	*ptr;
	t_ptr	**head;

	head = return_ptr();
	ptr = malloc(size);
	if (!ptr)
		ft_free_all(ERR_MALLOC, 1);
	add_ptr(ptr, head, place, type);
	return (ptr);
}
