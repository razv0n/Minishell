/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 0000/04/17 11:56:05 by mfahmi            #+#    #+#             */
/*   Updated: 2025/05/13 12:04:09 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

bool    split_arg(t_info *info)
{
    char **words;
    int i;
    t_list *node;

    i = 0;
    words = ft_split_tokens(info);
    info->words = words;
    if (!words)
        ft_free(info, ERR_MALLOC);
    while (words[i])
    {
        node = ft_lstnew_d(words[i]);
        if (!node)
            ft_free(info, ERR_MALLOC);
        ft_lstadd_back_d(&info->head_cmd, node);
        i++;
    }
    if (check_error(info))
    {
        info->head_cmd = NULL;
        return (false);
    }
    return (true);
}
