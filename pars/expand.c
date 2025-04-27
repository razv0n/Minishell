/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 20:24:54 by mfahmi            #+#    #+#             */
/*   Updated: 2025/04/27 15:44:06 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

char    *ft_strchrprev(const char *str, int c)
{
    size_t  i;

    i = 0;
    while (str[i])
    {
        if (str[i] == (unsigned char)c)
            return (str[i] = '\0', return(char *)str);
        i++;
    }
    if (!c)
        return ((char *)str + i);
    return (NULL);
}

void    remove_quotes(char *str)
{
    char *start;
    char *end;

    str = ft_strchr(str, '"');
    str
    
}

void    expand(t_info *info)
{
    char *prev;
    char *next;
    char *exapnded;

    while (info-head_cmd)
    {
        if (info->head_cmd->content[0] == '"' || info->head_cmd->conetnt[0] == '$')
        {
            remove_quotes(info->head_cmd->content); // remove the quotes\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
            if (ft_strchr(info->head_cmd->content, '$'))
            {
                prev = ft_strchr(info->head_cmd->content, '$');
            }
        }
        info->head_cmd = info->head_cmd->next;
    }    
}