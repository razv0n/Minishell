/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yezzemry <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:02:53 by yezzemry          #+#    #+#             */
/*   Updated: 2025/04/14 19:03:18 by yezzemry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char	*ft_strjoin(char *s1, char *s2)
{
	char	*out;
	int	i;
	int	j;
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
	return (out);
}

void	create_node(xp **head, char *tmp)
{
	xp	*node;
	xp	*p;

	if (!head || !tmp)
		return ;
	node = malloc(sizeof(xp));
	if (!node)
		return ;
	node->str = tmp;
	node->next = NULL;
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
	}
}

int	parse_var(char *s)
{
	int	i;

	i = 0;
	if (!(s[i] >= 'a' && s[i] <= 'z') && !(s[i] >= 'A' && s[i] <= 'Z')
		&& !(s[i] == '_'))
		return (1);
	while (s[i] && ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z')
		|| (s[i] >= '0' && s[i] <= '9') || s[i] == '_') && (s[i] != '='))
		i++;
	if (!s[i] || s[i] == '=')
		return (0);
	return (1);
}

void	add_to_export(xp **head, char *s)
{
	xp	*tmp;
	xp	*node;
	xp	*ptr;

	tmp = *head;
	ptr = NULL;
	if (parse_var(s))
		return ;
	while (tmp)
	{
		if (compare(tmp->str + 11, s, 1) >= 0)
			break;
		ptr = tmp;
		tmp = tmp->next;
	}
	node = malloc(sizeof(xp));
	if (!node)
		return ;
	node->str = ft_strjoin("declare -x ", s);
	if (!node->str)
		return ;
	node->next = NULL;
	if (ptr)
	{
		ptr->next = node;
		node->next = tmp;
	}
	else
	{
		node->next = *head;
		*head = node;
	}
}

void	ft_export(char **env, char *s, int i)
{
	xp	*head;
	char	*tmp;
	int	j;
	int	x;

	head = NULL;
	i = 0;
	x = 0;
	while (env[i + 1])
	{
		j = i + 1;
		while (env[j + 1])
		{
			if (compare(env[i], env[j], 0) > 0)
			{
				tmp = env[i];
				env[i] = env[j];
				env[j] = tmp;
			}
			j++;
		}
		tmp = ft_strjoin("declare -x ", env[x]);
		create_node(&head, tmp);
		x++;
		i++;
	}
	if (s)
		add_to_export(&head, s);
	xp *p;
	while (head)
	{
		printf("%s\n", head->str);
		p = head;
		head = head->next;
		free (p->str);
		free (p);
	}
	free (head);
}

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	int	i;

	i = 0;
	while (env[i])
		i++;
	ft_export(env, "1hi=", i);
	return 0;
}
