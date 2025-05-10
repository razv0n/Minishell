/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:14:08 by mfahmi            #+#    #+#             */
/*   Updated: 2025/05/10 12:07:01 by mfahmi           ###   ########.fr       */
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

bool    check_error(t_info *info)
{
    t_list *head;

    head = info->head_cmd;
    while (head)
    {
        if (!head->prev && is_pipe(head->content)) //* if first token is pipe we have error
            return (ft_free(info, SYNTAX_ERROR), 0); // free the list and words and return true for the function split_arg
        if (!head->next)
        { // if last token is pipe or redirections we have error
            if (is_pipe(head->content) || is_redirect(head->content))
                return (ft_free(info, SYNTAX_ERROR), 0);
        }
        else
        {
            if (is_pipe(head->content) && is_pipe(head->next->content)) // if two pipes in a row we have error
                return (ft_free(info, SYNTAX_ERROR), 0);
            if (is_redirect(head->content) && (is_redirect(head->next->content) || is_pipe(head->next->content))) // if two redirections in a row we have error
                return (ft_free(info, SYNTAX_ERROR), 0);
        }
        head = head->next;
    }
    return (false);
}
