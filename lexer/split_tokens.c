/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 0000/04/17 11:56:05 by mfahmi            #+#    #+#             */
/*   Updated: 2025/04/23 10:50:38 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void    split_arg(char *line, ft_list *head)
{
    char **words;
    int i;
    ft_list *node;


    words = ft_split(line); //? should not work with split >> << > < |
    i = 0;
    words = ft_split_tokens(line);
    if (!words)
        exit(1);
    while (words[i])
    {
        node = ft_lstnew_d(words[i]);
        if (!node)
        {
            ft_lstclear(head);
            fr_mem_split(words);
            exit(1);
        }
        ft_lsadd_back_d(&head, node);
        i++;
    }
}
