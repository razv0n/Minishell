/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:04:17 by mfahmi            #+#    #+#             */
/*   Updated: 2025/05/20 11:26:28 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void print_stack(t_list *head)
{
    // if (!head)
        // return ;
    while (head)
    {
        printf("\nhead->content [%s]  head->type [%d]  is_joined [%d]\n",head->content, head->type, head->joined);
        head = head->next;
    }
}

int main (int ac , char **av, char **env)
{
    t_info *info;

    signal(SIGINT, handle_sig);
    signal(SIGQUIT, handle_sig);
    (void) av;
    if (ac != 1)
    {
        printf ("minishell cannot run this\n");
        exit(1);
    }
    info = malloc(sizeof(t_info));
    info->head_env = NULL;
    cpy_env(env, info);
    while (1)
    {
        info->line = readline("╭━━[\033[1;36mminishell\033[0m]━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╮\n╰──➤");
        if (!info->line)
        {
            ft_free_all(info);
            printf("exit\n");
            exit(0);
        }
        if(info->line[0])
            add_history(info->line);
        if (pars(info) == -1) // ? dont forget to free the head after usi
            continue ;
        init_things(info, info->head_cmd);
        // print_stack(info->head_cmd, info);
        ft_free(info, 1337); //for printig linked list
    }
    return (-1);
}
