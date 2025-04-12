/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yezzemry <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:20:03 by yezzemry          #+#    #+#             */
/*   Updated: 2025/04/12 18:20:06 by yezzemry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
#include <stdio.h>

//i considered that the struct has a double pointer containing the cmd and it's arguments
//i didn't check if echo is valid or not

int	ft_strcmp(char *arg, char *str)
{
	int	i;

	i = 0;
	while (arg[i] && str[i])
	{
		if (arg[i] != str[i])
			return (0);
		i++;
	}
	if (arg[i] != ' ' || str[i])
		return (0);
	return (1);
}

void	ft_echo(char **arg)
{
	int	(i), nl;
	i = 1;
	if (ft_strcmp(arg[1], "-n"))
	{
		i = 2; //here i checked if there is a '-n' flag so i can skip it otherwise i write it
		nl = 1;
	}
	while (arg[i])
	{
		printf("%s", arg[i]);
		i++;
	}
	if (nl == 1)
		printf("\n");
}

int main()
{
	char *arg[] = {"echo", "-n", "i want to go", NULL};
	ft_echo(arg);
	return (0);
}
