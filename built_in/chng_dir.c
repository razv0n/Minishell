/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chng_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:40:36 by mfahmi            #+#    #+#             */
/*   Updated: 2025/05/08 14:40:37 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../Minishell.h"

void	ft_cd(char **arg)
{
	if (chdir(arg[1]) == -1)
	{
		write (2, "An error has occured while changing directory\n", 46);
		return ;
	}
	// should change in export and env from here
}

// #include <fcntl.h>
// int	main()
// {
// 	char s[100];
// 	printf("%s\n", getcwd(s, 100));
// 	char *arg[] = {"cd", "/home/yezzemry/Desktop/youness_br", NULL};
// 	ft_cd(arg);
// 	// open("youness", O_RDONLY | O_CREAT, 0777);
// 	printf("%s\n", getcwd(s, 100));
// 	return (0);
// }
