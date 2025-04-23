/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 0000/04/17 11:56:05 by mfahmi            #+#    #+#             */
/*   Updated: 2025/04/23 21:11:27 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void    split_arg(char *line, t_list **head)
{
    char **words;
    int i;
    t_list *node;

    i = 0;
    words = ft_split_tokens(line);
    if (!words)
        exit(1);
    while (words[i])
    {
        node = ft_lstnew_d(words[i]);
        if (!node)
        {
            fr_mem_split(sizeof(words) / sizeof(words[0]), words);
            exit(1);
        }
        ft_lstadd_back_d(head, node);
        i++;
    }
}
