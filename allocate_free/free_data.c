/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:23:12 by mfahmi            #+#    #+#             */
/*   Updated: 2025/05/31 19:08:29 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

char	**fr_mem_split(int index, char **result)
{
	// this function frees the memory allocated for the split_tokens
	while (index >= 0)
	{
		free(result[index]);
		index--;
	}
	free (result);
	return (NULL);
}
// this function frees the memory allocated for the list if we have a syntax error
bool	free_print(t_list *head, char **words)
{
	printf("\033[31msyntax error\033[0m\n");
	fr_mem_split(sizeof(words) / sizeof(words[0]), words);
	ft_lstclear_d(&head);
	return (true);
}

void ft_free(t_info *info, t_error_type err)
{
    ft_lstclear_d(&info->head_cmd);
    // free(info->words);
    free(info->joined);
    
    info->head_cmd = NULL;
    if (err == SYNTAX_ERROR)
        ft_putstr_fd("\033[31msyntax error\033[0m\n", 2);
    else if (err == FR_CHILD)
    {
        free(info->utils->cmd);
        free(info->utils->exc);
        // free_double(info->utils->path);
        free(info->utils);
        // ft_free_all();
    }
}
void    ft_perror(t_error_type msg)
{
    if (msg == ERR_MALLOC)
        ft_putstr_fd("Minishell : Memory allocation failed\n", 2);
    else if (msg == NORMAL)
        ft_putstr_fd("exit\n", 2);
}

void ft_free_all(t_error_type msg)
{
    t_ptr   *head;
    t_ptr *help;
    
    head = return_ptr();
    help = head;
    while (help)
    {
        if (help->type == F_SIMPLE)
            free(help->content);
        else if (help->type == F_DOUBLE)
            free_double(help->content);
        else
            ft_lstclear_d(help->content);// three types the first one is the simple one
        help = help->next;
    }
    ft_lstclear_not(&head);
    rl_clear_history();
    ft_perror(msg);
    exit(1);
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