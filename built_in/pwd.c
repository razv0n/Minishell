/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:46:52 by yezzemry          #+#    #+#             */
/*   Updated: 2025/05/05 11:32:35 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void	ft_pwd(void)
{
	char	s[1024];

	if (getcwd(s, 1024) == NULL)
	{
		write (2, 
			"An error has occured while getting current working directory\n", 61);
		return ;
	}
	printf("%s", s);
}

int	main()
{
	ft_pwd();
	return (0);
}
