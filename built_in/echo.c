/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:20:03 by yezzemry          #+#    #+#             */
/*   Updated: 2025/06/01 15:39:28 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int	check_new_line(char *s)
{
	if (!s)
		return (1);
	if (*s == '-')
		s++;
	if (*s == 'n')
		s++;
	return (*s);
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
	
	// printf("[0]%s  [1]%s\n", arg[1], arg[2]);
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
		if (arg[i + 1])
			write (1, " ", 1);
		i++;
	}
	if (nl == 1)
		write(1, "\n", 1);
}

// int main()
// {
// 	char *arg[] = {"echo", "-n n n n n ", "i want to go", NULL};
// 	ft_echo(arg);
// 	return (0);
// }
