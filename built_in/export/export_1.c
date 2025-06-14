/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 11:59:46 by yezzemry          #+#    #+#             */
/*   Updated: 2025/06/13 18:38:57 by mfahmi           ###   ########.fr       */
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
	while (s2[j] && s2[j] != '=') // !invalide add s[j-1 == 0 -1] != '='
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
		out = ft_malloc(sizeof(char) * (len + 3), FIRST_P);
	else
		out = ft_malloc(sizeof(char) * (len + 1), FIRST_P);
	while (s1[i])
	{
		out[i] = s1[i];
		i++;
	}
	fill_the_string(out, s2, *equal, i);
	return (out);
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
