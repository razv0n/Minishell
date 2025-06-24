/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 11:48:50 by mfahmi            #+#    #+#             */
/*   Updated: 2025/06/22 21:52:54 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_word_space(char const *str)
{
	size_t	i;
	int		count;
	int		sp;

	sp = 1;
	i = 0;
	if (str[i] == '\0')
		return (0);
	count = 0;
	while (str[i])
	{
		if (!is_whitespace(str[i]))
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


static char	*get_next_word(char const **s, char **result, int index)
{
	int			lenght;
	int			in;
	const char	*start;

	start = *s;
	in = 0;
	while (is_whitespace(**s) && **s != '\0')
		(*s)++;
	start = *s;
	while (!is_whitespace(**s) && **s != '\0')
		(*s)++;
	lenght = *s - start;
	result[index] = ft_malloc((lenght + 1) * sizeof(char), SECOUND_P, FREE);
	while (start < *s)
	{
		result[index][in] = *start;
		in++;
		start++;
	}
	result[index][in] = '\0';
	return (result[index]);
}

char	**ft_split_space(char const *s)
{
	char	**result;
	int		lenght;
	int		i;

	if (!s)
		return (NULL);
	lenght = count_word_space(s);
	result = ft_malloc((lenght + 1) * sizeof(char *), SECOUND_P, FREE);
	i = 0;
	while (i < lenght)
	{
		result[i] = get_next_word(&s, result, i);
		i++;
	}
	result[i] = NULL;
	return (result);
}

// int main()
// {
//     char **str = ft_split_space(" ");
//     printf("%s",str[0]);
// }