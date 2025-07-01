/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:46:52 by yezzemry          #+#    #+#             */
/*   Updated: 2025/06/27 21:27:21 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void	ft_pwd(t_info *info)
{
	char	s[4096];

	if (getcwd(s, sizeof(s)) == NULL)
	{
		// ft_putstr_fd("An error has occured while getting current working directory\n", 2);
		perror("pwd ");
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
