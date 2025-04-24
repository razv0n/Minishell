/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 21:26:42 by yezzemry          #+#    #+#             */
/*   Updated: 2025/04/23 23:06:17 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

// Here we need the exit status cuz we will need it to terminate with it the process
// EOF will be treated by readline func

void	ft_exit(int ext_st)
{
	printf("exit\n");
	exit (ext_st);
}

int	main()
{
	ft_exit(100);
	return 0;
}
