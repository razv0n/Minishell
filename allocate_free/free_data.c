/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:23:12 by mfahmi            #+#    #+#             */
/*   Updated: 2025/05/10 20:25:52 by mfahmi           ###   ########.fr       */
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
bool	free_print(t_list *head)
{
	printf("\033[31msyntax error\033[0m\n");
	ft_lstclear_d(&head);
	return (true);
}

void ft_free(t_info *info, t_error_type err)
{
	ft_lstclear_d(&info->head_cmd);
	free(info->words);
	free(info->joined);

	info->head_cmd = NULL;
	if (err == SYNTAX_ERROR)
		ft_putstr_fd("\033[31msyntax error\033[0m\n", 2);
	else if (err == FR_CHILD)
	{
		free(info->utils->cmd);
		// printf("1\n");
		free(info->utils->exc);
		// printf("2\n");
		free_path(info->utils->path);
		// printf("3\n");
		free(info->utils);
		ft_free_all(info);
	}
}
void ft_free_all(t_info *info)
{
	// free(info->line);
	ft_lstclear_not(&info->head_env);
	free(info->line);
	free(info);
	rl_clear_history();
	// ft_lstclear_d(&info->head_export);
}

// void *ft_malloc(void *ptr, size_t size)
// {
// 	ptr =ft_mallocsizeof(ptr) * size);
// 	if (!ptr)
// 	{
// 		perror(ERR_MALLOC);
// 		ft_free();
// 		exit(1);
// 	}
// }