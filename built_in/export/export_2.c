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
	node = malloc(sizeof(t_xp));
	if (!node)
		return (NULL);
	node->str = s;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	ft_export(t_xp **head, t_info *info)
{
	int	i;

	i = 1;
	while (info->utils->cmd[i])
	{
		if (add_to_export(head, info->utils->cmd[i], info))
			add_to_env(&info->head_env, info->utils->cmd[i]);
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
