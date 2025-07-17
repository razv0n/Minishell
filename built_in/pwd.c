/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:46:52 by yezzemry          #+#    #+#             */
/*   Updated: 2025/07/16 10:08:07 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void	ft_pwd(t_info *info)
{
	char	s[4096];

	if (getcwd(s, sizeof(s)) == NULL)
	{
		ft_putstr_fd(info->cw, 1);
		ft_putstr_fd("\n", 1);
		*(exit_status_nm()) = 1;
		if (info->utils->child)
			ft_free_all(NORMAL, 1);
		return ;
	}
	printf("%s\n", s);
	*(exit_status_nm()) = 0;
	if (info->utils->child)
		ft_free_all(NORMAL, 0);
}
