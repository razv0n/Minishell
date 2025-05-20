/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:23:12 by mfahmi            #+#    #+#             */
/*   Updated: 2025/05/20 10:30:25 by mfahmi           ###   ########.fr       */
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
        // free_path(info->utils->path);
        free(info->utils);
        ft_free_all(info);
    }
    else if (err == ERR_MALLOC)
        ft_free_all(info);
}
void ft_free_all(t_info *info)
{
    // free(info->line);
    // ft_lstclear_not(&info->head_env);
    // ft_lstclear_d(&info->head_export);
    // ft_lstclear_d(&info->head_export);
    free(info->line);
    free(info);
    rl_clear_history();
    // ft_lstclear_d(&info->head_export);
}

void add_ptr(void *ptr)
{
	static t_ptr *head;
	t_ptr *new_node;

	new_node = ft_lstnew_ptr(ptr);
	ft_lstadd_back_ptr(&head, new_node);
}

// void	*ft_malloc(void *ptr, size_t size)
// {
// 	ptr = malloc(size);
// 	if (!ptr)
// 	{
// 		perror(ERR_MALLOC);
// 		ft_free();
// 		exit(1);
// 	}
// 	add_ptr(ptr);
// 	return (ptr);
// }

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