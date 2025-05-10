/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 0000/04/17 11:56:05 by mfahmi            #+#    #+#             */
/*   Updated: 2025/05/10 18:31:51 by mfahmi           ###   ########.fr       */
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
    {
        free(info->line);
        ft_lstclear_d(&info->head_env);
        free(info->joined);
        free(info);
        exit(127);
    }
    while (words[i])
    {
        node = ft_lstnew_d(words[i]);
        if (!node)
        {
            // fr_mem_split(sizeof(words) / sizeof(words[0]), words);
            ft_lstclear_d(&info->head_env); //? free the env list
            ft_lstclear_d(&info->head_cmd);
            free(info->line);
            free(info->words);
            free(info->joined);
            free(info); // free the info struct
            exit(127);
        }
        ft_lstadd_back_d(&info->head_cmd, node);
        i++;
    }
    // fr_mem_split(sizeof(words) / sizeof(words[0]), words); // 
    if (check_error(info))
    {
        info->head_cmd = NULL;
        return (false);
    }
    return (true);
}
