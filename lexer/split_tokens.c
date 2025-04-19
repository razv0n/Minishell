/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 0000/04/17 11:56:05 by mfahmi            #+#    #+#             */
/*   Updated: 2025/04/18 15:11:36 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void    split_arg(char *line, ft_list *head)
{
    char **words;
    int i;
    ft_list *node; //?-> u should declare the head

    words = ft_split(line, ' '); // should not work with split
    i = 0;
    if (!words)
        exit(1);
    while (words[i])
    {
        node = ft_lstnew(words[i]);
        if (!node)
        {
            ft_lstclear(head);
            free(words);
            exit(1);
        }
        ft_lsadd_back(&head, node);
        i++;
    }
}