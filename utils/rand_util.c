/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rand_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 22:09:41 by mfahmi            #+#    #+#             */
/*   Updated: 2025/07/06 15:10:20 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void	exit_status(t_info *info)
{
	if (WIFSIGNALED(info->ext))
		info->ext = 128 + WTERMSIG(info->ext);
	else if (WIFEXITED(info->ext))
		info->ext = WEXITSTATUS(info->ext);
}

t_ptr	*where_is_fd(t_ptr *head, int fd)
{
	t_ptr	*return_node;

	return_node = NULL;
	while (head)
	{
		if (head->type == CLOSE && *((int *)(head->content)) == fd)
			return_node = head;
		head = head->next;
	}
	return (return_node);
}

bool	have_space(char *str)
{
	int	i;

	if (!str)
		return (false);
	if (!str[0])
		return (true);
	i = 0;
	while (str[i])
	{
		if (is_whitespace(str[i]))
			return (true);
		i++;
	}
	return (false);
}

bool	change_red_help(t_list **head, t_info *info)
{
	t_list	*help;
	char	*str;

	if ((*head)->next && !ft_strcmp((*head)->content, "<<")
		&& ft_strchr((*head)->next->content, '$')
		&& (*head)->next->content[0] != '\'')
	{
		str = ft_strdup((*head)->next->content, SECOUND_P);
		expand_2(&str, DOUBLE_Q, info);
		if (!str || ((*head)->next->content[0] != '"'
				&& count_word_space(str) > 1))
		{
			(*head)->type = AMBIGUOUS;
			info->ext = 1;
			ft_perror(ERR_AMBIGUOUS);
		}
	}
	if ((*head)->next)
		(*head)->next->type = (*head)->type;
	help = (*head)->next;
	remove_node_doubly(&info->head_cmd, (*head));
	(*head) = help;
	return (true);
}

t_sys_err	fail_sys_call(t_info *info)
{
	ft_perror(SYSCALL);
	info->ext = 1;
	if (ft_dupx(info->fd_in, 0, true) == SYS_FAIL)
		return (SYS_FAIL);
	if (ft_dupx(info->fd_out, 1, true) == SYS_FAIL)
		return (SYS_FAIL);
	return (SYS_FAIL);
}
