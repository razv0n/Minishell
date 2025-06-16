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
		if ((s1[i] == '=') && !s2[i])
			return (-200);
		if (((s1[i] == '=') && (s2[i] == '=')))
			return (200);
	}
	return (s1[i] - s2[i]);
}

int	ft_len(char *s, int *equal)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
			*equal = 1;
		i++;
	}
	return (i);
}

void	fill_the_string(char *out, char *s2, int equal, int i)
{
	int	j;

	j = 0;
	while (s2[j] && s2[j - 1] != '=')
	{
		out[i] = s2[j];
		i++;
		j++;
	}
	if (equal)
		out[i++] = '"';
	while (s2[j])
	{
		out[i] = s2[j];
		i++;
		j++;
	}
	if (equal)
		out[i] = '"';
	out[++i] = '\0';
}

char	*join_str(char *s1, char *s2, int cdt, int *equal)
{
	char	*out;
	int	i;
	int	len;
	int	help;

	i = 0;
	help = 0;
	if (!equal)
		equal = &help; // for the segfault
	if (!s2 || !cdt)
		return (NULL);
	len = ft_len(s2, equal) + 11;
	if (*equal)
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
	fill_the_string(out, s2, *equal, i);
	return (out);
}

void	attach_node(t_list **head, char *s)
{
	t_list	*node;
	t_list	*p;

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
