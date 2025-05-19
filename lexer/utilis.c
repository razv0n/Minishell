/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 06:28:43 by mfahmi            #+#    #+#             */
/*   Updated: 2025/05/13 14:38:18 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void	exit_status(t_info *info)
{
	// printf("exit :%d\n", info->ext);
	if (WIFSIGNALED(info->ext))
		info->ext += 128;
	else
		info->ext = WEXITSTATUS(info->ext);
		// printf("exit :%d\n", info->ext);
		// printf("exit :%d\n", info->ext);
}

void handle_sigint(int sig)
{
    if (sig == SIGINT)
    {
        printf("\n");
        rl_on_new_line();
        rl_replace_line("", 0); //! whene i remove it, it work normaly
        rl_redisplay();
    }
	// else if (sig == SIGCHLD)
	// {
		// printf("sigshld\n");
	// }
}

int	ft_strcmp(char *line, char *str)
{
	int	i;

	i = 0;
	if (!line || !str)
		return (0);
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

static int	count_word(char *str)
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
void	is_joined(char *s, t_info *info)
{
	static int i;

	if (ft_isprint(*s) && !check_metacharacter(s) && !is_whitespace(*s) && !check_metacharacter(s - 1))
		info->joined[i] = true;
	i++;
	if (!*s)
		i = 0;
}

static char	*get_next_word(char **s, char **result, int index, t_info *info)
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
	is_joined(*s, info);
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

char	**ft_split_tokens(t_info *info)
{
	char	**result;
	int		lenght;
	int		i;
	char	*line;

	line = info->line;
	if (!info)
		return (NULL);
	lenght = count_word(line); // 2
	result = malloc ((lenght + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	info->joined = malloc(sizeof(bool) * (lenght));
	if (!info->joined)
		return (free(result), NULL);
	ft_bzero(info->joined, sizeof(bool) * lenght);
	i = 0;
	while (i < lenght)
	{
		result[i] = get_next_word (&line, result, i, info);
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