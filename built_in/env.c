/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 21:15:28 by yezzemry          #+#    #+#             */
/*   Updated: 2025/05/05 11:33:07 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

//We should have something that holds the env variable such as a dbl ptr in the struct

void	ft_env(t_list *head_env)
{
	if (head_env == NULL)
		return ;
	while (head_env)
	{
		printf("%s\n", head_env->content);
		head_env = head_env->next;
	}
}

// int	main(int ac, char **av, char **env)
// {
// 	ft_env(env);
// 	return 0;
// }
