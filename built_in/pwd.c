/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:46:52 by yezzemry          #+#    #+#             */
/*   Updated: 2025/05/07 19:22:16 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void	ft_pwd(t_info *info)
{
	char	s[1024];

	if (getcwd(s, 1024) == NULL)
	{
		ft_putstr_fd("An error has occured while getting current working directory\n", 2);
		info->ext = 1;
		if (info->utils->child)
			exit(1);
	}
	printf("%s\n", s);
	info->ext = 0; // for updating the exit status but i think we won't need it
	if (info->utils->child)
		exit(0);
}
