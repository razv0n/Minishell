/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:04:17 by mfahmi            #+#    #+#             */
/*   Updated: 2025/05/08 11:08:03 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void print_stack(t_list *head, t_info *info)
{
    // if (!head)
        // return ;
    int i = 0;
    while (head)
    {
        printf("\nhead->content [%s]  head->type [%d]  is_joined [%d]\n",head->content, head->type, info->joined[i]);
        head = head->next;
        i++;
    }
}

int main (int ac , char **av, char **env)
{
    t_info *info;

    signal(SIGINT, handle_sigint);
    (void) av;
    if (ac != 1)
    {
        printf ("minishell cannot run this\n");
        exit(1);
    }
    info = malloc(sizeof(t_info));
    cpy_env(env, info);
    while (1)
    {
        info->line = readline("╭━━[\033[1;36mminishell\033[0m]━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╮\n╰──➤");
        if (!info->line)
        {
            printf("exit\n");
            return (1);
        }
        if(info->line[0])
            add_history(info->line);
        pars(info); // ? dont forget to free the head after using it
        init_things(info, info->head_cmd);
        print_stack(info->head_cmd, info);
        ft_free(info); //for printig linked list
    }
    return (-1);
}
