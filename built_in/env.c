/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 21:15:28 by yezzemry          #+#    #+#             */
/*   Updated: 2025/06/14 22:23:29 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

// We should have something that holds the env variable such as a dbl ptr in the struct
int	where_to_edit_env(t_list *tmp, t_list **ptr, char *s)
{
	int	res;

	res = 0;
	while (tmp)
	{
		res = compare(tmp->content, s, 1);
		if (res >= 0 && res != 200)
			return (1);
		else if (res == 200)
			return (-1);
		else if (res == -200)
			return (0);
		*ptr = tmp;
		tmp = tmp->next;
	}
	return (1);
}

void	add_to_env(t_list **head, char *s)
{
	t_list	*node;
	t_list	*prev;
	int		cdt;

	prev = NULL;
	cdt = where_to_edit_env(*head, &prev, s);
	node = ft_lstnew_d(ft_strdup(s, FIRST_P), FIRST_P);
	if (cdt == -1)
	{
		if (prev)
		{
			if (prev->next)
				node->next = prev->next->next;
			prev->next = node;
			node->prev = prev;
		}
		else
		{
			node->next = (*head)->next;
			*head = node;
		}
	}
	else
		ft_lstadd_back_d(head, node);
}

void	ft_env(t_list *head_env, char **cmd, t_info *info)
{
	if (head_env == NULL)
		return ;
	if (cmd[1])
	{
		write(2, "env: '", 6);
		write(2, cmd[1], length(cmd[1]));
		write(2, "': No such file or directory\n", 29);
		info->ext = 127;
		if (info->utils->child)
			ft_free_all(NORMAL, 127);
		return ;
	}
	while (head_env)
	{
		printf("%s\n", head_env->content);
		head_env = head_env->next;
	}
	info->ext = 0;
	if (info->utils->child)
		ft_free_all(NORMAL, 0);
}
