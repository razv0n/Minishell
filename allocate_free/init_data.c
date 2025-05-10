/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:32:59 by mfahmi            #+#    #+#             */
/*   Updated: 2025/05/10 12:05:20 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void    init_info(t_info *info)
{
    // info->head_env = NULL;
    info->head_cmd = NULL;
    info->joined = NULL;
    info->words = NULL;
}

void    get_head(void *ptr)
{
    static t_ptr *head;
    ft_lstadd_back_ptr(&head, ft_lstnew_ptr(ptr));
}

void    *ft_malloc (size_t size)
{
    void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		perror(ERR_MALLOC);
		// ft_free();// should free all
		exit(1);
	}
    get_head(ptr);
	return (ptr);
}