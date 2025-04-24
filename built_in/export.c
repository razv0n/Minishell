/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:02:53 by yezzemry          #+#    #+#             */
/*   Updated: 2025/04/23 23:06:07 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

typedef struct export
{
	char *str;
	struct export *next;
}	xp;

int	compare(char *s1, char *s2, int bl)
{
	int	i;

	i = 0;
	if (bl == 0)
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

char	*ft_strdup(char *s1, char *s2)
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

void	add_to_export(xp **head, char *s)
{
	xp	*tmp;
	xp	*node;
	xp	*ptr;

	tmp = *head;
	ptr = NULL;
	while (tmp->next)
	{
		if (compare(tmp->str + 11, s, 1) > 0)
			ptr = tmp;
		tmp = tmp->next;
	}
	node = malloc(sizeof(xp));
	if (!node)
		return ;
	node->str = ft_strdup("declare -x ", s);
	if (!node->str)
		return ;
	node->next = NULL;
	if (ptr)
	{
		tmp = ptr->next;
		ptr->next = node;
		node->next = tmp;
	}
	else
		tmp->next = node;
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
		tmp = ft_strdup("declare -x ", env[x]);
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

// int main(int ac, char **av, char **env)
// {
// 	(void)ac;
// 	(void)av;
// 	int	i;

// 	i = 0;
// 	while (env[i])
// 		i++;
// 	ft_export(env, "A=3428345", i);
// 	return 0;
// }
