/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:26:17 by mfahmi            #+#    #+#             */
/*   Updated: 2025/06/18 17:46:31 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void	type_tokens(t_list *head)
{
	while (head)
	{
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
	t_list	*help;

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

int	change_red(t_info *info)
{
	t_list	*head;
	t_list	*help;

	head = info->head_cmd;
	while (head)
	{
		if (is_redirect(head->content))
		{
			if (head->next && !head->next->content && !ft_strcmp(head->content, "<<"))
				ft_perror(AMBIGUOUS);

			if (head->next)
				head->next->type = head->type;
			help = head->next;
			remove_node_doubly(&info->head_cmd, head);
			head = help;
		}
		else
			head = head->next;
	}
	return (1);
}

int	pars(t_info *info)
{
	bool	syntax_error;

	syntax_error = false;
	if (!check_quotes_error(info))
	{
		if (!split_arg(info))
			syntax_error = true;
		type_tokens(info->head_cmd);
		add_is_joined(info->head_cmd, info);
		change_red(info);
		start_herdoc(info, info->head_cmd);
		if (syntax_error)
			return (-1);
		expand(info);
		joined_node(info);
		remove_the_null(&info->head_cmd);
		return (1);
	}
	return (-1);
}
