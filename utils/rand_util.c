/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rand_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 22:09:41 by mfahmi            #+#    #+#             */
/*   Updated: 2025/07/14 17:53:00 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void	exit_status(t_info *info)
{
	if (WIFSIGNALED(info->ext))
	{
		info->ext = 128 + WTERMSIG(info->ext);
		if (info->ext == 130)
			write(1, "\n", 1);
	}
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

void	change_red_help(t_list **head, t_info *info)
{
	t_list	*help;
	char	*str;

	if ((*head)->next && !ft_strcmp((*head)->content, "<<"))
	{
		str = type_red((*head)->next, info);
		if (!str)
		{
			(*head)->next->type = AMBIGUOUS;
			info->ext = 1;
			ft_perror(ERR_AMBIGUOUS);
		}
	}
	if ((*head)->next && (*head)->next->type != AMBIGUOUS)
		(*head)->next->type = (*head)->type;
	help = (*head)->next;
	remove_node_doubly(&info->head_cmd, (*head));
	(*head) = help;
}

t_sys_err	fail_sys_call(t_info *info, t_sys_err return_value)
{
	ft_putstr_fd(info->cmd_err, 2);
	ft_perror(SYSCALL);
	info->ext = 1;
	return (return_value);
}
