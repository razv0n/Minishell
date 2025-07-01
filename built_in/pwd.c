/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:46:52 by yezzemry          #+#    #+#             */
/*   Updated: 2025/07/01 17:18:36 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void	ft_pwd(t_info *info)
{
	char	s[4096];

	if (getcwd(s, sizeof(s)) == NULL)
	{
		perror("");
		info->ext = 1;
		if (info->utils->child)
			ft_free_all(NORMAL, 1);
		return ;
	}
	printf("%s\n", s);
	info->ext = 0; // for updating the exit status but i think we won't need it
	if (info->utils->child)
		ft_free_all(NORMAL, 0);
}
