/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metacharcter_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 22:06:28 by mfahmi            #+#    #+#             */
/*   Updated: 2025/07/13 16:19:15 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

bool	check_metacharcter_skip(const char *c, size_t *i)
{
	if ((c[*i] == '<' && c[*i + 1] == '<') || (c[*i] == '>'
			&& c[*i + 1] == '>'))
	{
		(*i)++;
		return (1);
	}
	else if (c[*i] == '|' || c[*i] == '<' || c[*i] == '>')
		return (1);
	return (0);
}

int	check_metacharacter(const char *c)
{
	if ((*c == '>' && *(c + 1) == '>') || (*c == '<' && *(c + 1) == '<'))
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

void	is_joined(char *s, int length, t_info *info)
{
	static int	i;

	if (*s && ft_isprint(*s) && !check_metacharacter(s) && !is_whitespace(*s)
		&& !check_metacharacter(s - 1))
		info->joined[i] = true;
	i++;
	if (i == length)
		i = 0;
}
