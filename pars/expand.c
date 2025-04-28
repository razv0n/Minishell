/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 20:24:54 by mfahmi            #+#    #+#             */
/*   Updated: 2025/04/28 12:06:04 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int     index_pos(char *str, char c) // return the index
{
    int i;

    i = 0;
    whike (str[i])
    {
        if (str[i] == c)
            return (i);
        i++;
    }
    return (-1);
}
char    *ft_strchrprev(const char *str, int c)
{
    size_t  i;

    i = 0;
    while (str[i])
    {
        if (str[i] == (unsigned char)c)
            return (str[i] = '\0', return(char *)str); // this line can make a leaks // check it
        i++;
    }
    if (!c)
        return ((char *)str + i);
    return (NULL);
}
int     lenght_is_alpha(char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        if (!ft_isalpha(str[i]))
            return (i);
        i++;
    }
    return (i);
}

void    remove_quotes(char *str)
{
    char *start;

    start = ft_strchr(str, '"');
    if (start)
    {
        str = strat;
        str = ft_strchrprev(str, '"'); // it should found the last quote because we found the first one
    }
}

void    expand(t_info *info)
{
    char *prev;
    char *next;
    char *exapnded;
    char *tmp;
    char *tmp_1;
    t_list content_cmd;

    conetnt_cmd = info->head;
    while (content->conetnt)
    {
        if (info->head_cmd->content[0] == '"' || info->head_cmd->conetnt[0] == '$')
        {
            if (ft_strchr(info->head_cmd->content, '$'))
            {
                remove_quotes(info->head_cmd->content); // remove the quotes
                printf("str after removing quotes %s\n", info->head_cmd->content);
                while (info->head_cmd->content[0])
                {
                    prev = info->head_cmd->content;
                    prev = ft_strchrprev(prev, '$');
                    tmp = ft_strchr(info->head_cmd->conetnt, '$') + 1;
                    if (ft_isalpha(*tmp))
                    {
                        expanded = ft_substr(info->head_cmd->content, index_pos(info->head_cmd->content, '$') + 1, lenght_is_alpha(tmp));
                        tmp_1 = exapnded;
                        expanded = getenv(expanded);
                        free(tmp_1);
                        prev = tmp_1;
                        prev = strjoin(prev , expanded);
                        free(tmp_1);
                    }
                    else
                    {
                        prev = ft_strjoin(prev, ft_substr(info->head_cmd->content, index_pos(info->head_cmd->content, '$'), index_pos(tmp, '$') - 1);
                    }
                    if (ft_strlen(prev) == ft_strlen(info->head_cmd->conetnt))
                        break;
                    else
                        info->head_cmd->content = ;
                }
            }
        }
        info->head_cmd = info->head_cmd->next;
    }
}