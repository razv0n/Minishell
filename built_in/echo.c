/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:20:03 by yezzemry          #+#    #+#             */
/*   Updated: 2025/05/08 14:32:55 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int	check_new_line(char *s)
{
	if (*s == '-')
		s++;
	if (*s == 'n')
		s++;
	return (*s - '\0');
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
		i = 2;
		nl = 0;
	}
	while (arg[i])
	{
		write (1, arg[i], ft_length(arg[i]));
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
