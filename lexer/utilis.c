/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 06:28:43 by mfahmi            #+#    #+#             */
/*   Updated: 2025/06/22 09:43:17 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

typedef struct help
{
	int		lenght;
	int		i;
	char	*start;
	int		index;
	char	quote;
}			t_variable_1;

typedef struct count_word_varibles
{
	size_t	i;
	int		count;
	bool	sp;
	bool	quotes;
	bool	quotes_next;
	bool	meta_next;
	bool	meta;
}			t_varibles;

void	check_state_count(t_varibles *vb)
{
	if (vb->meta_next && !vb->quotes_next)
	{
		vb->count++;
		vb->sp = 0;
		vb->meta_next = false;
	}
	else if (vb->quotes_next)
	{
		vb->count++;
		vb->sp = 1;
		vb->quotes_next = false;
	}
	else if (vb->sp == true || vb->meta)
	{
		vb->count++;
		vb->sp = 0;
	}
}

static int	count_word(char *str)
{
	t_varibles	vb;

	vb.sp = 1;
	vb.i = 0;
	vb.quotes_next = false;
	vb.meta_next =  false;
	if (str[0] == '\0')
		return (0);
	vb.count = 0;
	while (str[vb.i])
	{
		vb.meta = check_metacharcter_skip(str, &(vb.i));
		vb.quotes = quotes_in_split(str[vb.i]);
		if (!is_whitespace(str[vb.i]) && !vb.quotes)
			check_state_count(&vb);
		else if (!vb.quotes)
			vb.sp = 1;
		if (vb.meta)
			vb.meta_next = true;
		if (vb.quotes)
			vb.quotes_next = true;
		vb.i++;
	}
	return (vb.count);
}

static char	*add_to_res(char **s, char **result, t_variable_1 *vb)
{
	vb->lenght = *s - vb->start;
	result[vb->index] = ft_malloc((vb->lenght + 1) * sizeof(char), SECOUND_P, FREE);
	while (vb->start < *s)
	{
		result[vb->index][vb->i] = *(vb->start);
		vb->i++;
		vb->start++;
	}
	result[vb->index][vb->i] = '\0';
	return (result[vb->index]);
}

static char	*get_next_word(char **s, char **result, t_variable_1 *vb,
		t_info *info)
{
	vb->i = 0;
	while ((is_whitespace(**s) && **s != '\0'))
		(*s)++;
	vb->start = *s;
	if (check_quotes(**s))
	{
		vb->quote = **s;
		(*s)++;
		while (**s != vb->quote && **s != '\0')
			(*s)++;
		(*s)++;
	}
	else if (!check_metacharacter(*s))
		while ((**s != '\0' && (!check_metacharacter(*s)) && !is_whitespace(**s)
				&& !check_quotes(**s)))
			(*s)++;
	else
	{
		if (check_metacharacter(*s) == 2)
			*s += 2;
		else
			(*s)++;
	}
	is_joined(*s, info);
	return (add_to_res(s, result, vb));
}

char	**ft_split_tokens(t_info *info)
{
	char			**result;
	int				lenght;
	t_variable_1	vb;
	char			*line;

	line = info->line;
	if (!info)
		return (NULL);
	lenght = count_word(line);
	printf("count word = %d\n", lenght);
	result = ft_malloc((lenght + 1) * sizeof(char *), SECOUND_P, FREE);
	info->joined = ft_malloc(sizeof(bool) * (lenght), SECOUND_P, FREE);
	ft_bzero(info->joined, sizeof(bool) * lenght);
	vb.index = 0;
	while (vb.index < lenght)
	{
		result[vb.index] = get_next_word(&line, result, &vb, info);
		vb.index++;
	}
	result[vb.index] = NULL;
	return (result);
}
