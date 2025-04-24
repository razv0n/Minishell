/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:14:08 by mfahmi            #+#    #+#             */
/*   Updated: 2025/04/24 19:06:22 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

bool is_redirect(char *c)
{
    return (ft_strcmp(c, ">") || ft_strcmp(c, "<") || ft_strcmp(c, ">>")
            || ft_strcmp(c, "<<"));
}

bool is_pipe(char *c)
{
    return (ft_strcmp(c, "|"));
}

bool    check_error(t_list *head, char **words)
{
    while (head)
    {
        if (!head->prev && is_pipe(head->content)) //* if first token is pipe we have error
            return (free_print(head, words)); // free the list and words and return true for the function split_arg
        if (!head->next)
        { // if last token is pipe or redirections we have error
            if (is_pipe(head->content) || is_redirect(head->content))
                return (free_print(head, words));
        }
        else
        {
            if (is_pipe(head->content) && is_pipe(head->next->content)) // if two pipes in a row we have error
                return (free_print(head, words));
            if (is_redirect(head->content) && (is_redirect(head->next->content) || is_pipe(head->next->content))) // if two redirections in a row we have error
                return (free_print(head, words));
        }
        head = head->next;
    }
    return (false);
}
