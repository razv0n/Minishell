/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:20:03 by yezzemry          #+#    #+#             */
/*   Updated: 2025/07/05 14:09:28 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int	check_new_line(char *s)
{
	if (!s || !*s)
		return (1);
	if (*s == '-')
		s++;
	while (*s == 'n')
		s++;
	return (*s);
}

void	ft_echo(char **arg, t_info *info)
{
	int	i;
	int	nl;

	i = 1;
	nl = 1;
	while (!check_new_line(arg[i]))
	{
		i++;
		nl = 0;
	}
	while (arg[i])
	{
		write(STDOUT_FILENO, arg[i], length(arg[i]));
		if (arg[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (nl == 1)
		printf("\n");
	info->ext = 0;
	if (info->utils->child)
		ft_free_all(NORMAL, 0);
}

// int main()
// {
// 	char *arg[] = {"echo", "-n n n n n ", "i want to go", NULL};
// 	ft_echo(arg);
// 	return (0);
// }
