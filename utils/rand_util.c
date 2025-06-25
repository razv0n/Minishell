/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rand_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 22:09:41 by mfahmi            #+#    #+#             */
/*   Updated: 2025/06/22 15:00:10 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void	exit_status(t_info *info)
{
	if (WIFSIGNALED(info->ext))
		info->ext = 128 + WTERMSIG(info->ext);
	else
		info->ext = WEXITSTATUS(info->ext);
}


t_ptr   *where_is_fd(t_ptr *head, int   fd)
{
    t_ptr   *return_node;

    return_node = NULL;
    while (head)
    {
        if(head->type == CLOSE && *((int *)(head->content)) == fd)
            return_node = head;
        head = head->next;
    }
    return (return_node);
}

bool	check_lf_file(t_info *info)
{
	struct	stat st;

	if (!info->utils->exc)
		info->utils->exc = info->utils->cmd[0];
	if (stat(info->utils->cmd[0], &st) == -1)
		return (true);
	if (!access(info->utils->cmd[0], F_OK) && ft_strchr(info->utils->cmd[0], '/') && !S_ISDIR(st.st_mode))
	{
		if (!access(info->utils->cmd[0], X_OK))
			*(sig_varible()) = true;
		return (true);
	}
	// errno = ENOENT;
	return (false);
}

bool	have_space(char *str)
{
	int i;
	
	if (!str)
		return (false);
	if (!str[0])
		return (true);
	i = 0;
	while(str[i])
	{
		if (is_whitespace(str[i]))
			return(true);
		i++;
	}
	return (false);
}

// bool	check_fd_found(t_ptr *head, int fd)
// {
// 	while (head)
// 	{
// 		if (head->type == CLOSE && *(int *)head->content == fd)
// 			return (true);
// 		head = head->next;
// 	}
// 	return (false);
// }