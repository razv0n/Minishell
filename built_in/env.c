/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 21:15:28 by yezzemry          #+#    #+#             */
/*   Updated: 2025/06/12 15:35:53 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

//We should have something that holds the env variable such as a dbl ptr in the struct

void	add_to_env(t_list **head, char *s)
{
	t_list	*node;

	node = ft_lstnew_d(s, FIRST_P);
	if (!node)
		return ;
	ft_lstadd_back_d(head, node);
}

void	ft_env(t_list *head_env, char **cmd, t_info *info)
{
	if (head_env == NULL)
		return ;
	if (cmd[1])
	{
		write (2, "env: '", 6);
		write (2, cmd[1], length(cmd[1]));
		write (2, "': No such file or directory\n", 29);
		info->ext = 127;
		if (info->utils->child)
			ft_free_all(NORMAL ,127);
		return ;
	}
	while (head_env)
	{
		printf("%s\n", head_env->content);
		head_env = head_env->next;
	}
	info->ext = 0;
	if (info->utils->child)
		ft_free_all(NORMAL ,0);
}
