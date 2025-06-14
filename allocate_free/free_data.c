    /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:23:12 by mfahmi            #+#    #+#             */
/*   Updated: 2025/06/12 16:36:44 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void    ft_perror(t_error_type msg)
{
    if (msg == ERR_MALLOC)
        ft_putstr_fd("Minishell : Memory allocation failed\n", 2);
    else if (msg == EXIT)
        ft_putstr_fd("exit\n", 2);
    else if (msg == SYNTAX_ERROR)
        ft_putstr_fd("Minishell : \033[31msyntax error\033[0m\n", 2);
    else if (msg == ERR_CD)
        ft_putstr_fd("Minishell: cd: failed to change directory\n", 2);
}


// bool	free_print(t_list *head, char **words)
// {
// 	printf("\033[31msyntax error\033[0m\n");
// 	fr_mem_split(sizeof(words) / sizeof(words[0]), words);
// 	ft_lstclear_d(head);
// 	return (true);
// }

void ft_free(t_info *info, t_error_type msg)
{
    t_ptr **head;
    t_ptr *help;
    t_ptr   *next;

    head = return_ptr();
    help = *head;
    while (help)
    {
        if (help->place == SECOUND_P)
        {
            next = help->next;
            remove_node_single(head, help);
            help = next;
        }
        else
            help = help->next;
    }
    ft_perror(msg);
}

void ft_free_all(t_error_type msg, unsigned char exit_code)
{
    t_ptr   **head;

    head = return_ptr();
    ft_lstclear_not(head);
    rl_clear_history();
    ft_perror(msg);
    exit(exit_code);
}

// void	free_ptr(t _ptr **head)
// {
// 	t_ptr *temp;

// 	while (*head)
// 	{
// 		temp = *head;
// 		*head = (*head)->next;
// 		free(temp->content);
// 		free(temp);
// 	}
// 	*head = NULL;
// }