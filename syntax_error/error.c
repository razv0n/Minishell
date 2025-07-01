/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:14:08 by mfahmi            #+#    #+#             */
/*   Updated: 2025/06/18 17:07:09 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

bool	is_redirect(char *c)
{
	return (ft_strcmp(c, ">") || ft_strcmp(c, "<") || ft_strcmp(c, ">>")
		|| ft_strcmp(c, "<<"));
}

bool	is_pipe(char *c)
{
	return (ft_strcmp(c, "|"));
}

bool	check_error(t_info *info)
{
	t_list	*head;

	head = info->head_cmd;
	while (head)
	{
		if (!head->prev && is_pipe(head->content))
			return (ft_perror(SYNTAX_ERROR), 1);
		if (!head->next)
		{
			if (is_pipe(head->content) || is_redirect(head->content))
				return (ft_perror(SYNTAX_ERROR), 1);
		}
		else
		{
			if (is_pipe(head->content) && is_pipe(head->next->content))
				return (ft_perror(SYNTAX_ERROR), 1);
			if (is_redirect(head->content) && (is_redirect(head->next->content)
					|| is_pipe(head->next->content)))
				return (ft_perror(SYNTAX_ERROR), 1);
		}
		head = head->next;
	}
	return (false);
}
