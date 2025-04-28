/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:04:17 by mfahmi            #+#    #+#             */
/*   Updated: 2025/04/27 16:04:18 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void print_stack(t_list *head)
{
    // if (!head)
        // return ;
    while (head)
    {
        printf("head->countent %s  head->type %d\n",head->content, head->type);
        head = head->next;
    }
}


int main (int ac , char **av, char **env)
{
    char *line;
    t_info *info;

    signal(SIGINT, handle_sigint);
    (void) av;
    info = malloc(sizeof(t_info));
    if (ac != 1)
    {
        printf ("minishell cannot run this\n");
        exit(1);
    }
    while (1)
    {
        line = readline("╭━━[\033[1;36mminishell\033[0m]━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╮\n╰──➤");
        if (!line)
        {
            printf("exit\n");
            return (1);
        }
        add_history(line);
        pars(info, line, env); // ? dont forget to free the head after using it
        print_stack(info->head_cmd); //for printig linked list
        free(line);
    }
    return (0);
}
