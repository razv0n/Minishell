/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 21:26:42 by yezzemry          #+#    #+#             */
/*   Updated: 2025/05/05 11:32:22 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

// Here we need the exit status cuz we will need it to terminate with it the process
// EOF will be treated by readline func

// static int	length(char *s)
// {
// 	int	i;

// 	i = 0;
// 	if (s == NULL)
// 		return (0);
// 	while (s[i] != '\0')
// 		i++;
// 	return (i);
// }

int	convert(char *s, int *err)
{
	long	res;
	int		j;
	int		sign;

	res = 0;
	j = 0;
	sign = 1;
	if ((s[j] == '-' || s[j] == '+')
		&& (s[j + 1] >= '0' && s[j + 1] <= '9'))
	{
		if (s[j] == '-')
			sign *= -1;
		j++;
	}
	while (s[j] >= '0' && s[j] <= '9')
	{
		if ((res * 10 > 9223372036854775807)
			|| (-res * 10 < -9223372036854775807))
			*err = 1;
		res = res * 10 + s[j] - 48;
		j++;
	}
	if (s[j])
		*err = 1;
	return (res * sign);
}

void	ft_exit(char **cmd, int *ext, int child)
{
	int	n;
	int	err;

	err = 0;
	if (!child)
		write (2, "exit\n", 5);
	if (cmd[1])
	{	
		n = convert(cmd[1], &err);
		if (err)
		{
			write (2, "bash: exit: ", 12);
			write (2, cmd[1], length(cmd[1]));
			write (2, ": numeric argument required\n", 28);
			exit (2);
		}
		if (cmd[2])
		{
			write (2, "bash: exit: too many arguments\n", 31);
			*ext = 1;
			return ;
		}
	}
	exit (*ext);
}

// int	main()
// {
// 	char *arg[] = {"x", "29562369", "8347", NULL};
// 	ft_exit(arg, 8);
// 	return 0;
// }
