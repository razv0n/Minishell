/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:23:12 by mfahmi            #+#    #+#             */
/*   Updated: 2025/05/10 09:49:18 by mfahmi           ###   ########.fr       */
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
void ft_free(t_info *info)
{
	ft_lstclear_d(&info->head_cmd);
	// ft_lstclear_d((t_list)&info->head_export);
	// if (info->utils)
	// {
		// free(info->utils->cmd);
		// free(info->utils->path);
		// free(info->utils);
	// }
	// free(info->line);
	free(info->joined);
}


// void *ft_malloc(void *ptr, size_t size)
// {
// 	ptr = malloc(sizeof(ptr) * size);
// 	if (!ptr)
// 	{
// 		perror(ERR_MALLOC);
// 		ft_free();
// 		exit(1);
// 	}
// }