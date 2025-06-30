/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yezzemry <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 12:37:20 by yezzemry          #+#    #+#             */
/*   Updated: 2025/06/30 12:37:46 by yezzemry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

char	**collecte_cmds(t_list *head, t_u *utils)
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
	cmd[i] = NULL;
	return (cmd);
}

int	complete_check(char **path, t_info *info)
{
	int	i;
	char	*x;
	struct stat sb;

	i = 0;
	while (path && path[i])
	{
		x = add_string(path[i], info->utils->cmd[0]);
		if (!access(x, F_OK))
		{
			stat(x, &sb);
			if (!access(x, X_OK) && !S_ISDIR(sb.st_mode))
			{
				info->utils->bin = true;
				*(sig_varible()) = true;
				info->utils->exc = x;
				info->permi = false;
				return (1);
			}
			info->permi = true;
		}
		i++;
	}
	return (0);
}
