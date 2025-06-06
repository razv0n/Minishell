/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:36:22 by yezzemry          #+#    #+#             */
/*   Updated: 2025/06/01 17:00:56 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"



int	length(char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*add_string(char *s1, char *s2)
{
	int			i;
	int			j;
	char		*p;

	i = length(s1) + length(s2);
	p = malloc(sizeof(char) * (i + 1));
	if (p == NULL || s1 == NULL || s2 == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		p[i] = s2[j];
		i++;
		j++;
	}
	p[i] = '\0';
	return (p);
}

char	**update_path(char *s)
{
	char	**path;
	int		i;
	char	*tmp;

	if (!s)
		return (NULL);
	path = ft_split(s, ':');
	if (!path)
		return (NULL);
	i = 0;
	while (path[i])
	{
		tmp = path[i];
		path[i] = add_string(path[i], "/");
		free(tmp);
		if (!path[i])
			free_double(path);
		i++;
	}
	return (path);
}

int	count_pipes(t_list *head)
{
	int	i;

	i = 0;
	while (head)
	{
		if (head->type == PIPE)
			i++;
		head = head->next;
	}
	return (i);
}
