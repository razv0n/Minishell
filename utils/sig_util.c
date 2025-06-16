/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 21:36:28 by mfahmi            #+#    #+#             */
/*   Updated: 2025/06/13 21:03:13 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void	handle_sig(int sig)
{
	if (sig == SIGINT)
	{
		if (*(sig_varible()) == false)
		{
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0); //! when i remove it, it work normaly
			rl_redisplay();
		}
		else
		{
			printf("\n");
			*(sig_varible()) = false;
		}
	}
}

void	setup_signals(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, handle_sig);
	signal(SIGQUIT, handle_sig);
}

bool	*sig_varible(void)
{
	static bool	sig_varible;

	return (&sig_varible);
}
