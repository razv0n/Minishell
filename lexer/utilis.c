/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 06:28:43 by mfahmi            #+#    #+#             */
/*   Updated: 2025/05/04 13:59:50 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

#include "../Minishell.h"

void handle_sigint(int sig)
{
    if (sig == SIGINT)
    {
        printf("\n");
        rl_on_new_line();
        rl_replace_line("", 0); //! whene i remove it, it work normaly
        rl_redisplay();
    }
}

int	ft_strcmp(char *line, char *str)
{
	int	i;

	i = 0;
	while (line[i] && str[i])
	{
		if (line[i] != str[i])
			return (0);
		i++;
	}
	if (line[i] || str[i])
		return (0);
	return (1);
}

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
int check_metacharacter(const char  *c)
{
	if((*c == '>' && *(c + 1) == '>') || (*c == '<' && *(c + 1) == '<'))
		return (2);
    if (*c == '|' || *c == '>' || *c == '<')
        return (1);
    return (0);
}
bool	check_quotes(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}
bool	is_whitespace(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

static int	count_word(char const *str)
{
	size_t		i;
	int			count;
	bool			sp;
	bool check;
	bool quotes;
	bool check2;

	sp = 1;
	i = 0;
	check2 = true;
	if (str[i] == '\0')
		return (0);
	count = 0;
	while (str[i])
	{
		check = check_metacharcter_skip(str, &i);
		quotes = quotes_in_split(str[i]);
		if (!quotes)
			check2 = false;
		if (!is_whitespace(str[i]) && quotes)
		{
			if (check == true)
				sp = 1;
			if (!check2 && !sp)
			{
				sp = 1;
				check2 =  true;
			}
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
	while ((is_whitespace(**s) && **s != '\0'))
		(*s)++;
	start = *s;
	if (check_quotes(**s))
	{
		char ab = **s;
		(*s)++;
		while (**s != ab && **s != '\0')
			(*s)++;
		(*s)++;
	}
	else if (!check_metacharacter(*s))
	{
		while (((!check_metacharacter(*s)) && !is_whitespace(**s) && **s != '\0' && !check_quotes(**s)))
			(*s)++;
	}
	else
	{
		if (check_metacharacter(*s) == 2)
			*s += 2;
		else
			(*s)++;
	}
	// if (**s == '\'' || **s == '"')
		// (*s)++;
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