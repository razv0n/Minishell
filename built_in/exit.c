/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 21:26:42 by yezzemry          #+#    #+#             */
/*   Updated: 2025/07/13 15:52:55 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

char	*check_overflow(char *s, long *res, int sign, int *err)
{
	int	j;

	j = 0;
	while (s[j] >= '0' && s[j] <= '9')
	{
		if (j == 18)
		{
			if (sign == 1)
			{
				if (((*res) >= 922337203685477580) && s[j] > '7')
					*err = 1;
			}
			else if (sign == -1)
			{
				if (((*res) >= 922337203685477580) && s[j] > '8')
					*err = 1;
			}
		}
		// if ((((*res) * sign) > 922337203685477580)
		// 	|| (((*res) * sign) < -922337203685477580))
		// 	*err = 1;
		*res = (*res) * 10 + s[j] - 48;
		j++;
	}
	return (s + j);
}

char	*skip_spaces_zero(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] == ' ')
		i++;
	while (s[i] && s[i] == '0')
		i++;
	return (s + i);
}

int	convert(char *s, int *err)
{
	long	res;
	int		j;
	int		sign;

	res = 0;
	j = 0;
	sign = 1;
	if (!*s)
	{
		*err = 1;
		return (1);
	}
	s = skip_spaces_zero(s + j);
	if ((s[j] == '-' || s[j] == '+') && (s[j + 1] >= '0' && s[j + 1] <= '9'))
	{
		if (s[j] == '-')
			sign *= -1;
		j++;
	}
	s = skip_spaces_zero(s + j);
	s = check_overflow(s, &res, sign, err);
	if (s[0])
		*err = 1;
	return (res * sign);
}

void	ft_exit(char **cmd, int *ext, int child)
{
	int	err;

	err = 0;
	if (!child)
		ft_putstr_fd("exit\n", 2);
	if (cmd[1])
	{
		*ext = convert(cmd[1], &err);
		if (err)
		{
			ft_putstr_fd(ft_strjoin(ft_strjoin("exit: ", cmd[1], SECOUND_P),
					": numeric argument required\n", SECOUND_P), 2);
			ft_free_all(NORMAL, 2);
		}
		if (cmd[2])
		{
			ft_putstr_fd("exit: too many arguments\n", 2);
			*ext = 1;
			if (child)
				ft_free_all(NORMAL, 1);
			return ;
		}
	}
	ft_free_all(NORMAL, *ext);
}
