/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 21:36:28 by mfahmi            #+#    #+#             */
/*   Updated: 2025/07/10 17:17:41 by mfahmi           ###   ########.fr       */
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
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
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

int	count_herdoc(t_list *head)
{
	int	count_herdoc;

	count_herdoc = 0;
	while (head)
	{
		if (head->type == HEREDOC)
			count_herdoc++;
		head = head->next;
	}
	return (count_herdoc);
}

bool	check_if(t_type_word wich_quote, t_list *node)
{
	if (!node || !node->content || wich_quote == DOUBLE_Q
		|| wich_quote == SINGLE_Q || !node->content[0])
		return (false);
	return (true);
}
