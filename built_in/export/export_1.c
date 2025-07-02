/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 11:59:46 by yezzemry          #+#    #+#             */
/*   Updated: 2025/06/20 10:31:05 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

int	compare(char *s1, char *s2, bool b1, bool b2)
{
	int	i;

	i = 0;
	if (!b1)
	{
		while (s1[i] && s2[i] && s1[i] == s2[i])
			i++;
	}
	else
	{
		while (s1[i] && s2[i] && (s1[i] == s2[i])
			&& (s1[i] != '=' && s2[i] != '='))
			i++;
		if ((s1[i] == '=') && !s2[i])
			return (-200);
		if (((s1[i] == '=') && (s2[i] == '=')) || (!s1[i] && (s2[i] == '='))
			|| (!s1[i] && !s2[i]))
			return (200);
	}
	if (!b2)
		return (-1);
	return (s1[i] - s2[i]);
}

void	fill_the_string(char *out, char *s2, int equal, int i)
{
	int	j;

	j = 0;
	while (s2[j] && s2[j] != '=')
	{
		out[i] = s2[j];
		i++;
		j++;
	}
	if (equal)
	{
		out[i++] = '=';
		out[i++] = '"';
		j++;
	}
	while (s2[j])
	{
		out[i] = s2[j];
		i++;
		j++;
	}
	if (equal)
		out[i] = '"';
}

char	*join_str(char *s1, char *s2, int cdt, int *equal)
{
	char	*out;
	int		i;
	int		len;
	int		help;

	i = 0;
	help = 0;
	if (!equal)
		equal = &help;
	if (!s2 || !cdt)
		return (NULL);
	if (ft_strchr(s2, '='))
		*equal = 1;
	if (*equal)
		len = ft_strlen(s2) + 11 + 3;
	else
		len = ft_strlen(s2) + 11 + 1;
	out = ft_malloc(sizeof(char) * (len), FIRST_P, FREE);
	out[len - 1] = '\0';
	while (s1[i])
	{
		out[i] = s1[i];
		i++;
	}
	return (fill_the_string(out, s2, *equal, i), out);
}

void	attach_node(t_xp **head, char *s)
{
	t_xp	*node;
	t_xp	*p;

	node = create_node(s);
	if (!head)
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
