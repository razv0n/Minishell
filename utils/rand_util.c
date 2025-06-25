/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rand_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 22:09:41 by mfahmi            #+#    #+#             */
/*   Updated: 2025/06/25 16:33:48 by mfahmi           ###   ########.fr       */
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
	
	stat(info->utils->cmd[0], &st);
	info->utils->exc = info->utils->cmd[0];
	if (!access(info->utils->cmd[0], F_OK) && ft_strchr(info->utils->cmd[0], '/') && !S_ISDIR(st.st_mode))
	{
		if (!access(info->utils->cmd[0], X_OK))
			*(sig_varible()) = true;
		return (true);
	}
	errno = ENOENT;
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

void	change_red_help(t_list **head, t_info *info)
{	
	t_list	*help;
	char	*str;

		if ((*head)->next && !ft_strcmp((*head)->content, "<<") && ft_strchr((*head)->next->content, '$') && (*head)->next->content[0] != '\'' )
		{
			str = ft_strdup((*head)->next->content, SECOUND_P);
			expand_2(&str, DOUBLE_Q, info);
			if (!str || ((*head)->next->content[0] != '"' && count_word_space(str) > 1))
			{
				(*head)->type = AMBIGUOUS;
				ft_perror(ERR_AMBIGUOUS);
			}
		}
		if ((*head)->next)
			(*head)->next->type = (*head)->type;
		help = (*head)->next;
		remove_node_doubly(&info->head_cmd, (*head));
		(*head) = help;
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