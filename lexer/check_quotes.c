/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:13:17 by mfahmi            #+#    #+#             */
/*   Updated: 2025/06/11 18:45:06 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

typedef struct s_quote_state {
    char    stack[3];
    int     j;
    bool    single_quotes;
    bool    double_quotes;
} t_quote_state;

typedef struct quotes_split{
    short single_quotes;
    short double_quotes;
    bool single_quotes_b;
    bool double_quotes_b;
}quotes_split;

void reset_stack(t_quote_state *qs)
{
    ft_bzero(qs->stack, 3);
    qs->j = 0;
}

bool handle_single_quote(char c, t_quote_state *qs)
{
    if (c == '\'' && !qs->double_quotes)
    {
        qs->single_quotes = true;
        qs->stack[qs->j] = c;
        if (qs->j != 0 && qs->stack[qs->j - 1] == '\'')
        {
            reset_stack(qs);
            qs->single_quotes = false;
            return true;
        }
        qs->j++;
    }
    return false;
}

bool handle_double_quote(char c, t_quote_state *qs)
{
    if (c == '"' && !qs->single_quotes)
    {
        qs->double_quotes = true;
        qs->stack[qs->j] = c;
        if (qs->j != 0 && qs->stack[qs->j - 1] == '"')
        {
            reset_stack(qs);
            qs->double_quotes = false;
            return true;
        }
        qs->j++;
    }
    return false;
}

bool check_quotes_error(t_info *info)
{
    int i;
    t_quote_state qs;

    i = 0;
    ft_bzero(qs.stack, 3);
    qs.j = 0;
    qs.single_quotes = false;
    qs.double_quotes = false;

    while (info->line[i])
    {
        handle_single_quote(info->line[i], &qs);
        handle_double_quote(info->line[i], &qs);
        i++;
    }

    if (qs.stack[0])
    {
        ft_putstr_fd("\033[31msyntax error\033[0m\n", 2);
        return true;
    }
    return false;
}


bool quotes_in_split(char quotes)
{
    static quotes_split qs;

    if (quotes == '\'' && !qs.double_quotes_b)
    {
        qs.single_quotes_b = true;
        qs.single_quotes++;
        if (qs.single_quotes == 2)
        {
            qs.single_quotes_b = false;
            qs.single_quotes = 0;
        }
    }
    else if (quotes == '"' && !qs.single_quotes_b)
    {
        qs.double_quotes_b = true;
        qs.double_quotes++;
        if (qs.double_quotes == 2)
        {
            qs.double_quotes_b = false;
            qs.double_quotes = 0;
        }
    }
    if (!qs.single_quotes_b && !qs.double_quotes_b)
        return true;
    return false;
}
