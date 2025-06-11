/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:41:34 by mfahmi            #+#    #+#             */
/*   Updated: 2025/06/11 18:58:07 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_word(char const *str, char c)
{
	size_t		i;
	int			count;
	int			sp;

	sp = 1;
	i = 0;
	if (str[i] == '\0')
		return (0);
	count = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			if (sp)
			{
				count++;
				sp = 0;
			}
		}
		else
			sp = 1;
		i++;
	}
	return (count);
}

static char	**fr_mem_split(int index, char **result)
{
	while (index >= 0)
	{
		free(result[index]);
		index--;
	}
	free (result);
	return (NULL);
}

static char	*get_next_word(char const **s, char **result, char c, int index)
{
	int			lenght;
	int			in;
	const char	*start;

	start = *s;
	in = 0;
	while (**s == c && **s != '\0')
		(*s)++;
	start = *s;
	while (**s != c && **s != '\0')
		(*s)++;
	lenght = *s - start;
	result[index] = malloc ((lenght + 1) * sizeof(char));
	if (!result[index])
		return (NULL);
	while (start < *s)
	{
		result[index][in] = *start;
		in++;
		start++;
	}
	result[index][in] = '\0';
	return (result[index]);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		lenght;
	int		i;

	if (!s)
		return (NULL);
	lenght = count_word(s, c);
	result = malloc ((lenght + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	while (i < lenght)
	{
		result[i] = get_next_word (&s, result, c, i);
		if (!result)
			return (fr_mem_split(i, result));
		i++;
	}
	result[i] = NULL;
	return (result);
}
/*int main ()
{
     // char **sp = ft_split("#test#hello", '#');
     // char **sp = ft_split("#hhfe#banana#boom#." , '#');
      //char **sp = ft_split("booomlike" , ' ');
     char **sp = ft_split("\0aa\0bb" , '\0');
     //char **sp = ft_split(",,,,,,," , ',');
          printf("%s\n",sp[0]);
}*/
