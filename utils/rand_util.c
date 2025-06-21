/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rand_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 22:09:41 by mfahmi            #+#    #+#             */
/*   Updated: 2025/06/21 11:40:57 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void	exit_status(t_info *info)
{
	if (WIFSIGNALED(info->ext))
		info->ext = 128 + WTERMSIG(info->ext);
	else
		info->ext = WEXITSTATUS(info->ext);
}


t_ptr   *where_is_fd(t_ptr *head, int   fd)
{
    t_ptr   *return_node;

    return_node = NULL;
    while (head)
    {
        if(head->type == CLOSE && *((int *)(head->content)) == fd)
            return_node = head;
        head = head->next;
    }
    return (return_node);
}

// bool	check_fd_found(t_ptr *head, int fd)
// {
// 	while (head)
// 	{
// 		if (head->type == CLOSE && *(int *)head->content == fd)
// 			return (true);
// 		head = head->next;
// 	}
// 	return (false);
// }