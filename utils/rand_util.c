/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rand_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 22:09:41 by mfahmi            #+#    #+#             */
/*   Updated: 2025/06/16 17:06:27 by mfahmi           ###   ########.fr       */
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

bool	if_executable(t_info *info)
{
	struct	stat sb_1;
	bool	lf_found;

	lf_found = false;
	if (stat(info->utils->cmd[0], &sb_1) != -1)
		lf_found = true;
	if (lf_found && ft_strchr(info->utils->cmd[0], '/') && !S_ISDIR(sb_1.st_mode))
	{
		if (!access(info->utils->cmd[0], X_OK))
			*(sig_varible()) = true;
		info->utils->exc = info->utils->cmd[0];
		return (true);
	}
	errno = ENOENT;
	return (false);
}
