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

void	print_export(xp *head)
{
	while (head)
	{
		printf("%s\n", head->str);
		head = head->next;
	}
}

void	ft_export(xp **head, t_info *info)
{
	int	i;

	i = 1;
	while (info->utils->cmd[i])
	{
		if (add_to_export(head, info->utils->cmd[i], info))
			add_to_env(&info->head_env, info->utils->cmd[i]);
		return ;
	}
	print_export(*head);
	info->ext = 0;
	if (info->utils->child)
		exit(0);
}
