/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:13:17 by mfahmi            #+#    #+#             */
/*   Updated: 2025/05/12 14:32:06 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

bool    check_quotes_error (t_info *info)
{
    int i;
    int j;
    char stack[3];
    bool double_quotes;
    bool single_quotes;

    double_quotes = false;
    single_quotes = false;
    i = 0;
    j = 0;
    ft_bzero(stack, 3);
    while (info->line[i])
    {
        if (info->line[i] == '\'' && !double_quotes)
        {
            single_quotes = true;
            stack[j] = info->line[i];
            if (j != 0  && stack[j - 1] == '\'')
            {
                ft_bzero(stack, 3);
                j = -1;
                single_quotes = false;
            }
            j++;
        }
        else if (info->line[i] == '"' && !single_quotes)
        {
            double_quotes = true;
            stack[j] = info->line[i];
            if (j != 0 && stack[j - 1] == '"')
            {
                ft_bzero(stack, 3);
                j = -1;
                double_quotes = false;
            }
            j++;
        }
        i++;
    }
    if (stack[0])
    {
        ft_putstr_fd("\033[31msyntax error\033[0m\n", 2);
        return (true);
    }
    return (false);
}

bool quotes_in_split (char quotes)
{
    static short single_quotes;
    static short double_quotes;
    static bool single_quotes_b;
    static bool double_quotes_b;

    if (quotes == '\'' && !double_quotes_b)
    {
        single_quotes_b = true;
        single_quotes++;
        if (single_quotes == 2)
        {
            single_quotes_b = false;
            single_quotes = 0;
        }
    }
    else if (quotes == '"' && !single_quotes_b)
    {
        double_quotes_b = true;
        double_quotes++;
        if (double_quotes == 2)
        {
            double_quotes_b = false;
            double_quotes = 0;
        }
    }
    if (!single_quotes_b && !double_quotes_b)
        return true;
    else
        return false;
}
// void (char *line)
// {
//     int i;

//     i = 0;
//     if (line[i] == '|')
//         printf("syntax error\n");
//     i = ft_strlen(line) - 1; // check if the pipe is 
//     if (line[i] == '|')
//         printf("syntax error\n");
// }
