/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   absolute_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yezzemry <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:26:05 by yezzemry          #+#    #+#             */
/*   Updated: 2025/04/23 10:27:22 by yezzemry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main()
{
	t_list	*head = NULL;
	t_list	*node1 = malloc(sizeof(t_list));
	t_list	*node2 = malloc(sizeof(t_list));
	t_list	*node3 = malloc(sizeof(t_list));
	if (!node1 || !node2 || !node3)
		return (1);
	head = node1;
	node1->content = "ls";
	node1->prev = NULL;
	node1->type = ;
	node1->next = node2;

	node2->content = "-a";
	node2->prev = node1;
	node2->next = node3;

	node3->content = "|";
	node3->prev = node2;
	node3->next = node4;
}
// ./a.out "ls  -a | cat -e"
// ls
// -a
// |
// cat
// -e