/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 20:24:54 by mfahmi            #+#    #+#             */
/*   Updated: 2025/06/24 14:56:13 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

typedef struct
{
	int		i;
	char	*prev;
	char	buffer[2];
	char	*expand;
}			t_variable;

char	*check_to_expand(char *str, int *i, t_info *info)
{
	int		start;
	char	*expanded;

	expanded = NULL;
	start = *i + 1; // spkip the $
	if (!str[*i])
		return (NULL);
	if (ft_isalnum(str[*i + 1]) || str[*i + 1] == '_' || str[*i + 1] == '?')
	{
		(*i)++;
		if (ft_isalpha(str[*i]) || str[*i] == '_')
		{
			while (str[*i] && str[*i] != '?' && (ft_isalnum(str[*i])
					|| str[*i] == '_'))
				(*i)++;
		}
		else
			return (cas_in_expand(str, i, info));
		--(*i);
		expanded = ft_substr(str, start, *i - start + 1);
		return (go_to_expand(expanded, info->head_env));
	}
	else
		return (NULL);
}

void	expand_2(char **str, t_type_word wich_quote, t_info *info)
{
	t_variable	vb;

	if (wich_quote == SINGLE_Q)
		return ;
	vb.i = 0;
	vb.prev = NULL;
	vb.buffer[1] = '\0';
	while ((*str)[vb.i])
	{
		if ((*str)[vb.i] != '$')
		{
			vb.buffer[0] = (*str)[vb.i];
			vb.prev = ft_strjoin(vb.prev, vb.buffer, SECOUND_P);
		}
		else
		{
			vb.expand = check_to_expand(*str, &(vb.i), info);
			if (vb.expand)
				vb.prev = ft_strjoin(vb.prev, vb.expand, SECOUND_P);
			else if ((*str)[vb.i] == '$')
				vb.prev = ft_strjoin(vb.prev, "$", SECOUND_P);
		}
		vb.i++;
	}
	*str = ft_strdup(vb.prev, SECOUND_P);
}

void	expand(t_info *info)
{
	t_list	*content;
	t_list	*next_node;

	content = info->head_cmd;
	while (content)
	{
		if (content->content[0] == '$' && !content->content[1] && content->next
			&& content->joined && check_quotes(content->next->content[0]))
		{
			next_node = content->next;
			remove_node_doubly(&info->head_cmd, content);
			content = next_node;
			continue ;
		}
		if (check_quotes(content->content[0]))
			remove_quotes(&content->content, content);
		if (ft_strchr(content->content, '$') && content->type != HEREDOC)
		{
			expand_2(&content->content, content->quotes_type, info);
			split_variable(content->quotes_type, content);
		}
		content = content->next;
	}
}

void	ft_addnode(t_list *node, char *str)
{
	t_list	*new_node;
	
	if (!node)
		return ;
	new_node = ft_lstnew_d(str, SECOUND_P);
	new_node->next = node->next;
	if (node->next)
		node->next->prev = new_node;
	node->next = new_node;
	new_node->prev = node;
	new_node->type = WORD;
	new_node->joined = false;
}

void	split_variable(t_type_word wich_quote, t_list *node)
{
	char	**str_split;
	int		i;

	i =  1;
	// printf()
	if (!node || !node->content || wich_quote == DOUBLE_Q || wich_quote == SINGLE_Q)
		return;
	if (node->joined && is_whitespace(node->content[ft_strlen(node->content) - 1]))
		node->joined = false;
	str_split  = ft_split_space(node->content);
	if (!str_split[0])
		return;
	node->content = NULL;
	node->content = str_split[0];	
	while (str_split[i])
	{
		ft_addnode(node, str_split[i]);
		node = node->next;
		i++;
	}
}
