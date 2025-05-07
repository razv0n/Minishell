/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:20:03 by yezzemry          #+#    #+#             */
/*   Updated: 2025/05/07 19:29:16 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

//i considered that the struct has a double pointer containing the cmd and its arguments
//i didn't check if echo is valid or not
// hi youness this is moncef: i ve decided that we should work with a linked list
// Lets assume we have the input: echo -n "msg1""msg2""msg3" we will split this into a linked list in our case we ignore spaces inside quotes so each word becomes a node in the list you should loop through the list to find the echo command and recognize that its the command we need to handl the command is always expected to come first also everything after echo should be considered as one argument

int	check_new_line(char *s)
{
	if (*s == '-')
		s++;
	if (*s == 'n')
		s++;
	return (*s - '\0');
	// int	i;

	// i = 0;
	// if (s[i] == '-')
	// 	i++;
	// while (s[i] && (s[i] == 'n'))
	// 	i++;
	// // if (s[i])
	// // 	return (1);
	// return (s[i] - '\0');
}

int	ft_length(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_echo(char **arg)
{
	int	i;
	int	nl;

	i = 1;
	nl = 1;
	if (!check_new_line(arg[1]))
	{
		i = 2; //here i checked if there is a '-n' flag so i can skip newline otherwise i write it
		nl = 0;
	}
	while (arg[i])
	{
		write (1, arg[i], ft_length(arg[i]));
		// if (arg[i + 1])
		// 	write (1, " ", 1);
		i++;
	}
	if (nl == 1)
		printf("\n");
}

// int main()
// {
// 	char *arg[] = {"echo", "-n n n n n ", "i want to go", NULL};
// 	ft_echo(arg);
// 	return (0);
// }
