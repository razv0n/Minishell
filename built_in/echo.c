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

#include "../minishell.h"

//i considered that the struct has a double pointer containing the cmd and it's arguments
//i didn't check if echo is valid or not
// hi youness this is moncef: i ve decided that we should work with a linked list
//Lets assume we have the input: echo -n "msg1""msg2""msg3" we will split this into a linked list in our case we ignore spaces inside quotes so each word becomes a node in the list you should loop through the list to find the echo command and recognize that its the command we need to handl the command is always expected to come first also everything after echo should be considered as one argument
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
		i = 2; //here i checked if there is a '-n' flag so i can skip newline otherwise i write it
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
	// if (execve(arg[0], arg, NULL) == -1)
	// 	printf("error\n");
	ft_echo(arg);
	return (0);
}
