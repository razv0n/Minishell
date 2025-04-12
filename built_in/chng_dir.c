/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chng_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yezzemry <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:20:48 by yezzemry          #+#    #+#             */
/*   Updated: 2025/04/12 18:21:03 by yezzemry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
#include <unistd.h>

void	ft_cd(char **arg)
{
	if (chdir(arg[1]) == -1)
		write (2, "An error has occured while changing directory\n", 46);
}

#include <stdio.h>
int	main()
{
	char s[100];
	printf("%s\n", getcwd(s, 100));
	char *arg[] = {"cd", "../", NULL};
	ft_cd(arg);
	printf("%s\n", getcwd(s, 100));
	return (0);
}
