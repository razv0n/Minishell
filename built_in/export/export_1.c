/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yezzemry <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 11:59:46 by yezzemry          #+#    #+#             */
/*   Updated: 2025/05/29 11:59:59 by yezzemry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

int	compare(char *s1, char *s2, int bl)
{
	int	i;

	i = 0;
	if (!bl)
	{
		while (s1[i] && s2[i] && s1[i] == s2[i])
			i++;
	}
	else
	{
		while (s1[i] && s2[i] && (s1[i] == s2[i]) && (s1[i] != '=' && s2[i] != '='))
			i++;
		if (((s1[i] == '=') && (s2[i] == '=')) || !s2[i])
			return (1000); // bcause when i have a variable a=1 and b=1 b replaces a due to the condition that was if res == -1 change the value
	}
	return (s1[i] - s2[i]);
}

int	ft_len(char *s, int *sp)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
			*sp = 1;
		i++;
	}
	return (i);
}

void	fill_the_string(char *out, char *s2, int sp, int i)
{
	int	j;

	j = 0;
	while (s2[j] && s2[j - 1] != '=')
	{
		out[i] = s2[j];
		i++;
		j++;
	}
	if (sp)
		out[i++] = '"';
	while (s2[j])
	{
		out[i] = s2[j];
		i++;
		j++;
	}
	if (sp)
		out[i] = '"';
	out[++i] = '\0';
}

char	*join_str(char *s1, char *s2)
{
	char	*out;
	int	i;
	int	len;
	int	sp;

	i = 0;
	sp = 0;
	if (!s2)
		return (NULL);
	len = ft_len(s2, &sp) + 11;
	if (sp)
		out = malloc(sizeof(char) * (len + 3));
	else
		out = malloc(sizeof(char) * (len + 1));
	if (!out)
		return (NULL);
	while (s1[i])
	{
		out[i] = s1[i];
		i++;
	}
	fill_the_string(out, s2, sp, i);
	return (out);
}

void	attach_node(t_xp **head, char *s)
{
	t_xp	*node;
	t_xp	*p;

	node = create_node(s);
	if (!head || !node)
		return ;
	if (!*head)
	{
		*head = node;
		return ;
	}
	else
	{
		p = *head;
		while (p->next)
			p = p->next;
		p->next = node;
		node->prev = p;
	}
}
