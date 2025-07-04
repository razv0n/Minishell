/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:26:17 by mfahmi            #+#    #+#             */
/*   Updated: 2025/07/04 11:13:08 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void	type_tokens(t_list *head)
{
	while (head)
	{
		head->quotes_type = 1337;
		if (ft_strcmp(head->content, "<"))
			head->type = REDIRECT_IN;
		else if (ft_strcmp(head->content, ">"))
			head->type = REDIRECT_OUT;
		else if (ft_strcmp(head->content, "<<"))
			head->type = HEREDOC;
		else if (ft_strcmp(head->content, ">>"))
			head->type = APPEND;
		else if (is_pipe(head->content))
			head->type = PIPE;
		else
			head->type = WORD;
		head = head->next;
	}
}

void	joined_node(t_info *info)
{
	t_list	*head;
	int		i;

	head = ft_lstlast(info->head_cmd);
	i = 0;
	while (head)
	{
		if (head->joined && head->next)
		{
			head->content = ft_strjoin(head->content, head->next->content,
					SECOUND_P);
			if (head->quotes_type != SINGLE_Q && head->quotes_type != DOUBLE_Q)
				head->quotes_type = head->next->quotes_type;
			remove_node_doubly(&info->head_cmd, head->next);
		}
		head = head->prev;
		i++;
	}
}

void	add_is_joined(t_list *head, t_info *info)
{
	int	i;

	i = 0;
	while (head)
	{
		head->joined = info->joined[i];
		i++;
		head = head->next;
	}
}

bool	change_red(t_info *info)
{
	t_list	*head;

	head = info->head_cmd;
	while (head)
	{
		if (is_redirect(head->content))
		{
			if (!change_red_help(&head, info))
			{
				info->ext = 1;
				return (false);
			}
		}
		else
			head = head->next;
	}
	return (true);
}

int	pars(t_info *info)
{
	bool	ambiguous;

	if (!check_quotes_error(info))
	{
		if (!split_arg(info))
			return (-1);
		type_tokens(info->head_cmd);
		add_is_joined(info->head_cmd, info);
		ambiguous = change_red(info);
		if (start_herdoc(info, info->head_cmd) == SYS_FAIL)
			return (fail_sys_call(info));
		if (!ambiguous || info->sigint_herdoc)
			return (-1);
		expand(info);
		joined_node(info);
		remove_the_null(&info->head_cmd);
		return (1);
	}
	return (-1);
}
