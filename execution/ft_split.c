/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yezzemry <yezzemry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:27:40 by yezzemry          #+#    #+#             */
/*   Updated: 2025/03/06 18:07:12 by yezzemry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

static int	count_w(const char *s, char c)
{
	int	i;
	int	count;
	int	b;

	i = 0;
	count = 0;
	b = 1;
	while (s[i])
	{
		if (s[i] == c)
			b = 1;
		else if (b == 1)
		{
			b = 0;
			count++;
		}
		i++;
	}
	return (count);
}

static int	*length_wrd(char const *s, char c, int z)
{
	int	i;
	int	x;
	int	start;
	int	*arr;

	x = 0;
	arr = malloc(sizeof(int) * z);
	if (arr == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		while ((s[i] == c) && s[i])
			i++;
		if (s[i] == '\0')
			break ;
		start = i;
		while ((s[i] != c) && s[i])
			i++;
		arr[x] = i - start;
		x++;
	}
	return (arr);
}

static char	**copying(char **p, const char *s, char c)
{
	int	i;
	int	y;
	int	x;

	i = 0;
	y = 0;
	x = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] == '\0')
			break ;
		while ((s[i] != c) && s[i])
		{
			p[y][x] = s[i];
			x++;
			i++;
		}
		p[y][x] = '\0';
		x = 0;
		y++;
	}
	return (p);
}

static char	**ft_free(char **p, int *arr)
{
	int	i;

	i = 0;
	if (arr)
		free (arr);
	while (p[i] != NULL)
	{
		free (p[i]);
		i++;
	}
	free (p);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**p;
	int		*arr;

	int (i), z;
	z = count_w(s, c);
	i = 0;
	arr = length_wrd(s, c, z);
	if (arr == NULL)
		return (NULL);
	p = malloc(sizeof(char *) * (z + 1));
	if (p == NULL)
	{
		free (arr);
		return (NULL);
	}
	while (i < z)
	{
		p[i] = malloc(sizeof(char) * (arr[i] + 1));
		if (p[i] == NULL)
			return (ft_free(p, arr));
		i++;
	}
	p[z] = NULL;
	free (arr);
	return (copying(p, s, c));
}
