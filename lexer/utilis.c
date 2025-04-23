/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 06:28:43 by mfahmi            #+#    #+#             */
/*   Updated: 2025/04/23 15:41:48 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

bool check_metacharcter_skip(const char *c, size_t *i)
{
	if ((c[*i] == '<' && c[*i + 1] == '<') || (c[*i] == '>' && c[*i + 1] == '>'))
	{
		(*i)++;
		return (1);
	}
	else if (c[*i] == '|' || c[*i] == '<' || c[*i] == '>')
		return (1);
	return (0);
}
bool check_metacharacter(char c)
{
    if (c == '|' || c == '>' || c == '<')
        return (1);
    return (0);
}


static int	count_word(char const *str)
{
	size_t		i;
	int			count;
	bool			sp;
	bool check;

	sp = 1;
	i = 0;
	if (str[i] == '\0')
		return (0);
	count = 0;
	while (str[i])
	{
		check = check_metacharcter_skip(str, &i);
		if (!(str[i] >= 9 && str[i] <= 13) && str[i] != ' ' && quotes_in_split(str[i]))
		{
			if (check == true)
				sp = 1;
			if (sp == true)
			{
				count++;
				if (check == false)
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
	while (((**s >= 9 && **s <= 13) || **s == ' ') && **s != '\0')
		(*s)++;
	start = *s;
	if (**s == '\'' || **s == '"')
	{
		char ab = **s;
		(*s)++;
		while (**s != ab && **s != '\0')
			(*s)++;
	}
	else if (!check_metacharacter(**s))
	{
		while (((!check_metacharacter(**s)) && !(**s >= 9 && **s <= 13)) &&  **s != ' ' && **s != '\0')
			(*s)++;
	}
	else
	{
		while (check_metacharacter(**s) && **s != '\0')
			(*s)++;
	}
	if (**s == '\'' || **s == '"')
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

char	**ft_split_tokens(char const *s)
{
	char	**result;
	int		lenght;
	int		i;

	if (!s)
		return (NULL);
	lenght = count_word(s); // 2
	result = malloc ((lenght + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	while (i < lenght)
	{
		result[i] = get_next_word (&s, result, i);
		if (!result)
			return (fr_mem_split(i, result));
		i++;
	}
	result[i] = NULL;
	return (result);
}
// int main (int ac , char **av)
// {
// //      // char **sp = ft_split("#test#hello", '#');
// //      // char **sp = ft_split("#hhfe#banana#boom#." , '#');
// //       //char **sp = ft_split("booomlike" , ' ');
//      char **sp = ft_split_tokens(av[1]);
//      int i;
// 	 //char **sp = ft_split(",,,,,,," , ',');
// 	 for (i = 0; sp[i] ; i++)
//           printf("%s\n",sp[i]);
// 	fr_mem_split(i,sp);
// }