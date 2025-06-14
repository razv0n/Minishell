/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:09:21 by mfahmi          #+#    #+#             */
/*   Updated: 2025/05/05 11:36:28 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int	compare_2(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && (s2[i] != '=') && (s1[i] == s2[i]))
		i++;
	return (s2[i]);
}

void	unset_export(t_xp **head, char *s)
{
	t_xp	*tmp;
	t_xp	*p;

	tmp = *head;
	p = NULL;
	while (tmp)
	{
		if (!compare_2(tmp->str + 11, s))
			break;
		p = tmp;
		tmp = tmp->next;
	}
	if (tmp)
	{
		if (!p)
			*head = (*head)->next;
		else
			p->next = tmp->next;
		// free (tmp->str);
		// free (tmp);
	}
}

void	unset_env(t_list **head, char *s)
{
	t_list	*tmp;
	t_list	*p;

	tmp = *head;
	p = NULL;
	while (tmp)
	{
		if (!compare_2(tmp->content, s))
			break;
		p = tmp;
		tmp = tmp->next;
	}
	if (tmp)
	{
		if (!p)
		{
			p = *head;
			*head = (*head)->next;
			(*head)->prev = NULL;
			free (p);
			return ;
		}
		tmp->prev->next = tmp->next;
		if (tmp->next)
			tmp->next->prev = tmp->prev;
		// free (tmp);
	}
}

void	ft_unset(t_info *info, char **cmd)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		unset_export(&info->head_export, cmd[i]);
		unset_env(&info->head_env, cmd[i]);
		i++;
	}
	info->ext = 0;
	if (info->utils->child)
		ft_free_all(NORMAL, 0);
}
