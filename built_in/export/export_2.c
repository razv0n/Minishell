/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 12:00:04 by yezzemry          #+#    #+#             */
/*   Updated: 2025/07/16 10:22:47 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

void	print_export(t_xp *head)
{
	while (head)
	{
		printf("%s\n", head->str);
		head = head->next;
	}
}

t_xp	*create_node(char *s)
{
	t_xp	*node;

	if (!s)
		return (NULL);
	node = ft_malloc(sizeof(t_xp), FIRST_P, FREE);
	node->str = s;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	ft_export(t_xp **head, t_info *info)
{
	int	i;
	int	cdt;

	i = 1;
	while (info->utils->cmd[i])
	{
		cdt = add_to_export(head, info->utils->cmd[i]);
		if (cdt)
			add_to_env(&info->head_env, info->utils->cmd[i]);
		if (!info->utils->cmd[i + 1])
		{
			if (info->utils->child)
				ft_free_all(NORMAL, *(exit_status_nm()));
			return ;
		}
		i++;
	}
	print_export(*head);
	*(exit_status_nm()) = 0;
	if (info->utils->child)
		ft_free_all(NORMAL, 0);
}
