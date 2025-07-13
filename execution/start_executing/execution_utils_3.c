/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 12:37:20 by yezzemry          #+#    #+#             */
/*   Updated: 2025/07/06 15:10:02 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

void	get_next_cmd(t_info *info, t_list **head)
{
	while (*head)
	{
		if ((*head)->next && (*head)->next->type == PIPE)
			break ;
		*head = (*head)->next;
	}
	info->utils->cmd[0] = NULL;
}

t_sys_err	back_to_normal(t_info *info)
{
	// info->utils->fail = 0;
	if (info->utils->exc)
		info->utils->exc = NULL;
	if (info->utils->npi == -1)
		if (ft_dupx(info->fd_in, 0, true) == SYS_FAIL)
			return (SYS_FAIL);
	if (ft_dupx(info->fd_out, 1, true) == SYS_FAIL)
		return (SYS_FAIL);
	return (SYS_SUCCESS);
}

char	**collecte_cmds(t_list *head)
{
	int		i;
	t_list	*tmp;
	char	**cmd;

	i = 0;
	tmp = head;
	while (head && (head->type != PIPE))
	{
		if (head->type == WORD)
			i++;
		head = head->next;
	}
	cmd = ft_calloc (sizeof(char *), ++i);
	i = 0;
	head = tmp;
	while (head && (head->type != PIPE))
	{
		if (head->type == WORD)
			cmd[i++] = head->content;
		head = head->next;
	}
	cmd[i] = NULL; // if calloc sets all the pointers to NULL then this line is useless
	return (cmd);
}

int	complete_check(char **path, t_info *info)
{
	int			i;
	char		*x;
	struct stat	sb;

	i = 0;
	while (path && path[i])
	{
		x = add_string(path[i], info->utils->cmd[0]);
		stat(x, &sb);
		if (!access(x, F_OK) && !S_ISDIR(sb.st_mode))
		{
			if (!access(x, X_OK))
			{
				info->utils->bin = true;
				*(sig_varible()) = true;
				info->utils->exc = x;
				info->permi = false;
				return (1);
			}
			info->permi = true; // should we output the whole path where permission denied was found like bash or not
		}
		i++;
	}
	return (0);
}
