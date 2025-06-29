/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 21:36:28 by mfahmi            #+#    #+#             */
/*   Updated: 2025/06/29 11:58:54 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void	handle_sig(int sig)
{
	if (sig == SIGINT)
	{
		if (*(sig_varible()) == false)
		{
			write(1, "\n", 1);
			rl_replace_line("", 0); //! when i remove it, it work normaly
			rl_on_new_line();
			rl_redisplay();
		}
		else
		{
			write(1, "\n", 1);
			*(sig_varible()) = false;
		}
	}
}

void	setup_signals(void)
{
	signal(SIGINT, handle_sig);
	signal(SIGQUIT, SIG_IGN);
}

bool	*sig_varible(void)
{
	static bool	sig_varible;

	return (&sig_varible);
}


