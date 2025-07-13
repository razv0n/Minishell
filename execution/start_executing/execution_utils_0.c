/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_0.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:26:05 by mfahmi          	#+#    #+#            */
/*   Updated: 2025/06/02 12:10:24 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

t_sys_err	get_path(t_info *info, t_u *utils)
{
	utils->bin = false;
	// if (utils->fail != -1)
	// {
	if (!utils->child)
	{
		if (check_builtin(info, info->utils->cmd))
			return (SYS_SUCCESS);
	}
	if (utils->cmd[0])
	{
		if (utils->child)
		{
			if (execute_cmd(info, 0) == SYS_FAIL)
				return (SYS_FAIL);
		}
		else
		{
			if (execute_cmd(info, 1) == SYS_FAIL)
				return (SYS_FAIL);
		}
		utils->bin = true; // check if it works without
	}
	// }
	// ft_close(1);
	return (SYS_SUCCESS);
}

t_sys_err	open_pipe(t_u *utils)
{
	if (utils->i)
	{
		if (ft_dupx(utils->copy, 0, true) == SYS_FAIL)
			return (SYS_FAIL);
		ft_close(utils->copy);
	}
	if (utils->npi)
	{
		if (ft_pipe(utils->pi) == SYS_FAIL)
			return (SYS_FAIL);
		if (ft_dupx(utils->pi[1], 1, true) == SYS_FAIL)
			return (SYS_FAIL);
		utils->copy = ft_dupx(utils->pi[0], -1, false);
		if (utils->copy == SYS_FAIL)
			return (SYS_FAIL);
		utils->i = true;
		ft_close(utils->pi[0]);
		ft_close(utils->pi[1]);
	}
	utils->npi--;
	return (SYS_SUCCESS);
}

void	start_executing2(t_info *info)
{
	// if (info->ext != 127)
	waitpid(info->utils->id, &info->ext, 0);
	while (wait(NULL) != -1)
		;
	*(sig_varible()) = false;
	if (info->utils->bin)
		exit_status(info);
}

t_sys_err	start_executing(t_info *info, t_list *head, t_u *utils)
{
	while (head)
	{
		utils->cmd = collecte_cmds(head);
		if (open_pipe(utils) == SYS_FAIL)
			return (fail_sys_call(info));
		while (head && (head->type != PIPE))
		{
			if (head->type == AMBIGUOUS)
				get_next_cmd(info, &head);
			else if (head->type != WORD)
				if (redirection(head, head->type, info) == SYS_FAIL)
					return (fail_sys_call(info));
			if (head)
				head = head->next;
		}
		if (get_path(info, utils) == SYS_FAIL
			|| back_to_normal(info) == SYS_FAIL)
			return (fail_sys_call(info));
		if (head)
			head = head->next;
	}
	start_executing2(info);
	return (SYS_SUCCESS);
}

void	init_things(t_info *info, t_list *head)
{
	info->utils = ft_calloc(sizeof(t_u), 1);
	info->utils->cmd = NULL;
	info->utils->exc = NULL;
	info->utils->copy = 0;
	info->utils->i = false;
	info->utils->bin = false;
	info->utils->id = 0;
	// info->utils->fail = 0;
	info->utils->npi = count_pipes(head);
	info->utils->child = false;
	if (info->utils->npi)
		info->utils->child = true;
	// info->utils->path = update_path(ft_getenv("PATH", info->head_env));
	if (start_executing(info, head, info->utils) == SYS_FAIL)
	{
		if (ft_dupx(info->fd_in, 0, true) == SYS_FAIL)
			return ;
		if (ft_dupx(info->fd_out, 1, true) == SYS_FAIL)
			return ;
	}
	ft_close(info->fd_in);
	ft_close(info->fd_out);
}
