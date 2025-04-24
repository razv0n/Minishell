/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:26:17 by mfahmi            #+#    #+#             */
/*   Updated: 2025/04/24 22:48:41 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void    type_tokens(t_list *head)
{
    while (head)
    {
        if (ft_strcmp(head->content, "<"))
            head->type = REDIRECT_IN;
        else if (ft_strcmp(head->content, ">"))
            head->type = REDIRECT_OUT;
        else if (ft_strcmp(head->content, "<<"))
            head->type = HEREDOC;
        else if (ft_strcmp(head->content, ">>"))
            head->type = APPEND;
        else if (is_pipe(head->content))
            head->type = PIPE;
        else
            head->type = WORD;
        head = head->next;
    }
}

void    pars(char *line , t_list **head)
{
    check_quotes(line);
    split_arg(line, head);
    type_tokens(*head);
}