/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 0000/04/17 11:56:05 by mfahmi            #+#    #+#             */
/*   Updated: 2025/07/13 18:30:33 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void	remove_the_null(t_list **head)
{
	t_list	*help;

	help = *head;
	if (!help)
		return ;
	while (help)
	{
		if (!help->content && help->type != AMBIGUOUS)
			remove_node_doubly(head, help);
		help = help->next;
	}
}

void	remove_quote(t_list *head)
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

char	*type_red(t_list *head, t_info *info)
{
	char		*str;
	t_type_word	wich_quotes;

	wich_quotes = false;
	str = ft_strdup(head->content, SECOUND_P);
	if (check_quotes(str[0]))
		remove_quotes(&str, head);
	if (ft_strchr(head->content, '$') && head->content[0] != '\'')
	{
		expand_2(&str, wich_quotes, info);
		if (head->quotes_type != DOUBLE_Q && ((count_word_space(str) > 1)
				|| (head->joined && count_word_space(str) == 1
					&& is_whitespace(str[ft_strlen(str) - 1]))))
			return (NULL);
	}
	if (type_red2(head, str, info, wich_quotes) == false)
		return (NULL);
	return (str);
}

bool	type_red2(t_list *head, char *str, t_info *info,
		t_type_word wich_quotes)
{
	char	*str_1;

	while (head->joined && head)
	{
		if (head->next)
		{
			str_1 = ft_strdup(head->next->content, SECOUND_P);
			help_norm(str_1, head);
			if (head->next && head->next->content[0] != '\''
				&& ft_strchr(head->next->content, '$'))
			{
				expand_2(&str_1, wich_quotes, info);
				if (head->next->quotes_type != DOUBLE_Q
					&& ((count_word_space(str_1) > 1)
					|| (count_word_space(str_1) == 1
							&& is_whitespace(str_1[0])) || (head->next->joined
							&& count_word_space(str_1) == 1
							&& is_whitespace(str_1[ft_strlen(str_1) - 1]))))
					return (false);
			}
			str = ft_strjoin(str, str_1, SECOUND_P);
		}
		head = head->next;
	}
	return (true);
}
