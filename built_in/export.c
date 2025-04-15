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

int	compare(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	ft_len(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(char *s1, char *s2)
{
	char	*out;
	int	(i), j, len;

	i = 0;
	if (!s2)
		return (NULL);
	len = ft_len(s2) + 11;
	out = malloc(sizeof(char) * (len + 1));
	if (!out)
		return (NULL);
	while (s1[i])
	{
		out[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		out[i] = s2[j];
		i++;
		j++;
	}
	out[i] = '\0';
	// printf("%s\n", out);
	return (out);
}

void    ft_export(char **env, int i)
{
	char	**xp;
	char	*tmp;
	int	(j), x;

	xp = malloc(sizeof(char *) * i);
	if (!xp)
		exit (1);
	i = 0;
	x = 0;
	while (env[i + 1])
	{
		j = i + 1;
		while (env[j + 1])
		{
			if (compare(env[i], env[j]) > 0)
			{
				tmp = env[i];
				env[i] = env[j];
				env[j] = tmp;
			}
			j++;
		}
		xp[x] = ft_strdup("declare -x ", env[x]);
		x++;
		i++;
	}
	xp[x] = NULL;
	i = 0;
	while (xp[i])
	{
		printf("%s\n", xp[i]);
		free (xp[i]);
		i++;
	}
	free (xp);
}

// int main(int ac, char **av, char **env)
// {
// 	(void)ac;
// 	(void)av;
// 	int	i;

// 	i = 0;
// 	while (env[i])
// 		i++;
// 	ft_export(env, i);
// 	return 0;
// }
