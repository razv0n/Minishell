/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 21:15:28 by yezzemry          #+#    #+#             */
/*   Updated: 2025/07/16 11:24:59 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int	where_to_edit_env(t_list *tmp, t_list **ptr, char *s)
{
	int	res;

	res = 0;
	while (tmp)
	{
		res = compare(tmp->content, s, true, false);
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
	if (cdt == -1)
	{
		if (prev)
			prev->next->content = ft_strdup(s, FIRST_P);
		else
			(*head)->content = ft_strdup(s, FIRST_P);
	}
	else
	{
		node = ft_lstnew_d(ft_strdup(s, FIRST_P), FIRST_P);
		ft_lstadd_back_d(head, node);
	}
}

void	ft_env(t_list *head_env, char **cmd, t_info *info)
{
	if (head_env == NULL)
		return ;
	if (cmd[1])
	{
		ft_putstr_fd("env: with no options or arguments\n", 2);
		*(exit_status_nm()) = 1;
		if (info->utils->child)
			ft_free_all(NORMAL, 1);
		return ;
	}
	while (head_env)
	{
		printf("%s\n", head_env->content);
		head_env = head_env->next;
	}
	*(exit_status_nm()) = 0;
	if (info->utils->child)
		ft_free_all(NORMAL, 0);
}
