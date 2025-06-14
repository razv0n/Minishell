/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 22:15:19 by mfahmi            #+#    #+#             */
/*   Updated: 2025/06/13 17:50:00 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void    remove_quotes(char **str, t_list *node)
{
    int lenght;
    char c;

    c = *str[0];
    lenght =  ft_strlen(*str) - 2;
    *str = ft_substr(*str, 1, lenght);
    if (c == '\'')
        node->quotes_type = SINGLE_Q;
    else
        node->quotes_type = DOUBLE_Q;
}

char *go_to_expand (char *str, t_list *head_env)
{
    char *expand;
    
    expand = ft_getenv(str, head_env);
    return (expand);
}

char    *cas_in_expand(char *str, int *i, t_info *info)
{
    char *itoa_str;

    itoa_str = NULL;
    if (str[*i] == '?')
        itoa_str = ft_itoa(info->ext);
    return (itoa_str);
}