/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yezzemry <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 21:15:28 by yezzemry          #+#    #+#             */
/*   Updated: 2025/04/13 21:15:54 by yezzemry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

//We should have something that holds the env variable such as a dbl ptr in the struct

void	ft_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}

int	main(int ac, char **av, char **env)
{
	ft_env(env);
	return 0;
}
