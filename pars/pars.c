/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:26:17 by mfahmi            #+#    #+#             */
/*   Updated: 2025/05/04 10:47:09 by mfahmi           ###   ########.fr       */
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

void    cpy_env(char **env, t_info *info)
{
    int i;
    t_list *node;

    i = 0;
    while (env[i])
    {
        node = ft_lstnew_d(env[i]);
        if (!node)
        {
            ft_lstclear_d(&info->head_env);
            free(info->line);
            free(info); // free the info struct
            exit(1);
        }
        ft_lstadd_back_d(&info->head_env, node);
        i++;
    }
}

void    pars(t_info *info, char *line , char **env)
{
    init_info(info, line, env); // copy env to linked list
    if (!check_quotes_error(info))
    {
        split_arg(info);
        type_tokens(info->head_cmd);
        expand(info);
        remove_the_null(&info->head_cmd);
    }
}