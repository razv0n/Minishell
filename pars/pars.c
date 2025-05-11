/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:26:17 by mfahmi            #+#    #+#             */
/*   Updated: 2025/05/11 13:33:56 by mfahmi           ###   ########.fr       */
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
    info->head_env->joined = false;
    create_export(info, env, i);
}

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*help;

	if (!lst)
		return (NULL);
	help = lst;
	while (help->next != NULL)
		help = help->next;
	return (help);
}

void   joined_node(t_info *info)
{
    t_list *head;
    int i;
    char *tmp;
    t_list *help;

    head = ft_lstlast(info->head_cmd);
    i = 0;
    while (head)
    {
        if (head->joined && head->next)
        {
            tmp = head->content;
            head->content = ft_strjoin(head->content, head->next->content);
            free(tmp);
            remove_node(&info->head_cmd, head->next);
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
    free(info->joined);
    info->joined = NULL;
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
            if (!head->next)
            {
                ft_putstr_fd("\033[31ambiguous redirect\033[0m\n", 2);
                return (-1);
            }
            head->next->type = head->type;
            help = head->next;
            remove_node(&info->head_cmd, head);
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
        expand(info);
        remove_the_null(&info->head_cmd);
        joined_node(info);
        if (change_red(info) == - 1)
            return (-1);
    }
    return (1);
}
