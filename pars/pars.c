/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:26:17 by mfahmi            #+#    #+#             */
/*   Updated: 2025/06/12 21:23:19 by mfahmi           ###   ########.fr       */
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

void   joined_node(t_info *info)
{
    t_list  *head;
    int     i;
    t_list  *help;

    head = ft_lstlast(info->head_cmd);
    i = 0;
    while (head)
    {
        if (head->joined && head->next)
        {
            head->content = ft_strjoin(head->content, head->next->content);
            if (head->quotes_type != SINGLE_Q && head->quotes_type != DOUBLE_Q) // why i use this?
                head->quotes_type = head->next->quotes_type;
            remove_node_doubly(&info->head_cmd, head->next);
        }
        head = head->prev;
        i++;
    }
}

void      add_is_joined(t_list *head, t_info *info)
{
    int i;

    i = 0;
    while (head)
    {
        head->joined = info->joined[i];
        i++;
        head = head->next;
    }
}

int change_red(t_info *info)
{
    t_list *head;
    t_list *help;

    head = info->head_cmd;
    while (head)
    {
        if (is_redirect(head->content))
        {
            if (head->next && !head->next->content && !ft_strcmp(head->content, "<<"))
            {
                ft_putstr_fd("\033[31ambiguous redirect\033[0m\n", 2);
                return (ft_free(info, 1337), -1);
            }
            head->next->type = head->type;
            help = head->next;
            remove_node_doubly(&info->head_cmd, head);
            head = help; 
        }
        else
            head = head->next;
    }
    return (1);
}

int    pars(t_info *info)
{
    init_info(info); // copy env to linked list
    if (!check_quotes_error(info))
    {
        if (!split_arg(info))
            return (-1);
        type_tokens(info->head_cmd);
        add_is_joined(info->head_cmd, info);
        if (change_red(info) == -1)
            return (-1);
        expand(info);
        joined_node(info);
        start_herdoc(info, info->head_cmd);
        return (1);
    }
    return (-1);
}
