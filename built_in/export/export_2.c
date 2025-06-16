/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yezzemry <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 12:00:04 by yezzemry          #+#    #+#             */
/*   Updated: 2025/05/29 12:00:17 by yezzemry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

void	print_export(t_list *head)
{
	while (head)
	{
		printf("%s\n", head->str);
		head = head->next;
	}
}

t_list	*create_node(char *s)
{
	t_list	*node;

	if (!s)
		return (NULL);
	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->str = s;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	ft_export(t_list **head, t_info *info)
{
	int	i;
	int	cdt;

	i = 1;
	while (info->utils->cmd[i])
	{
		cdt = add_to_export(head, info->utils->cmd[i], info);
		if (cdt)
			add_to_env(&info->head_env, info->utils->cmd[i], cdt);
		if (!info->utils->cmd[i + 1])
		{
			if (info->utils->child)
				exit(info->ext);
			return ;
		}
		i++;
	}
	print_export(*head);
	info->ext = 0;
	if (info->utils->child)
		exit(0);
}
