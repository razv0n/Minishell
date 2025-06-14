/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 0000/04/17 11:56:05 by mfahmi            #+#    #+#             */
/*   Updated: 2025/06/13 11:22:51 by mfahmi           ###   ########.fr       */
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
    // info->words = words;
    // if (!words)
    //     ft_free(info, ERR_MALLOC);
    while (words[i])
    {
        node = ft_lstnew_d(words[i], SECOUND_P);
        ft_lstadd_back_d(&info->head_cmd, node);
        i++;
    }
    if (check_error(info))
    {
        info->head_cmd = NULL;
        info->ext = 2;
        return (false);
    }
    return (true);
}
