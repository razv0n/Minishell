/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 0000/04/17 11:56:05 by mfahmi            #+#    #+#             */
/*   Updated: 2025/06/22 17:42:08 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void	remove_the_null(t_list	**head)
{
	t_list	*help;

	help = *head;
	if (!help)
		return;
	while (help)
	{
		if (!help->content && help->type != AMBIGUOUS)
			remove_node_doubly(head, help);
		help = help->next;
	}
}

void	remove_quote(t_list	*head)
{
	while (head)
	{
		if (check_quotes(head->content[0]))
			remove_quotes(&head->content, head);
		head = head->next;
	}
}

bool	split_arg(t_info *info)
{
	char	**words;
	int		i;
	t_list	*node;

	i = 0;
	words = ft_split_tokens(info);
	while (words[i])
	{
		node = ft_lstnew_d(words[i], SECOUND_P);
		ft_lstadd_back_d(&info->head_cmd, node);
		i++;
	}
	if (check_error(info))
	{
		info->ext = 2;
		return (false);
	}
	return (true);
}
