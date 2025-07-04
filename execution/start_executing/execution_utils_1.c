/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:35:37 by yezzemry          #+#    #+#             */
/*   Updated: 2025/07/04 16:56:03 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

void	check_access2(t_info *info)
{
	if (!info->utils->path)
	{
		info->utils->exc = info->utils->cmd[0];
		return ;
	}
	else if (!*(info->utils->cmd[0]) || ft_strcmp(info->utils->cmd[0], ".")
		|| ft_strcmp(info->utils->cmd[0], "..")
		|| !complete_check(info->utils->path, info))
	{
		info->utils->error = 1;
		return (check_which_msg(info->utils->cmd[0], info));
	}
}

void	check_access(t_info *info)
{
	char		*slash;
	struct stat	sb;

	info->utils->error = 0;
	info->permi = false;
	slash = ft_strchr(info->utils->cmd[0], '/');
	if (slash)
	{
		if (stat(info->utils->cmd[0], &sb) == -1) // ./main
			return (check_which_msg(info->utils->cmd[0], info));
		if (!access(info->utils->cmd[0], F_OK | X_OK) && S_ISREG(sb.st_mode))
		{
			info->utils->exc = info->utils->cmd[0];
			return ;
		}
		else
		{
			if (S_ISDIR(sb.st_mode))
				errno = EISDIR;
			else
				info->permi = true;
			return (check_which_msg(info->utils->cmd[0], info));
		}
	}
	check_access2(info);
}

int	check_builtin_2(t_info *info, char **cmd)
{
	if (ft_strcmp(cmd[0], "pwd"))
	{
		ft_pwd(info);
		return (1);
	}
	else if (ft_strcmp(cmd[0], "cd"))
	{
		ft_cd(info, cmd);
		return (1);
	}
	else if (ft_strcmp(cmd[0], "echo"))
	{
		ft_echo(cmd, info);
		return (1);
	}
	else if (ft_strcmp(cmd[0], "unset"))
	{
		ft_unset(info, cmd);
		return (1);
	}
	return (0);
}

int	check_builtin(t_info *info, char **cmd)
{
	if (ft_strcmp(cmd[0], "export"))
	{
		ft_export(&info->head_export, info);
		return (1);
	}
	else if (ft_strcmp(cmd[0], "exit"))
	{
		ft_exit(cmd, &info->ext, info->utils->child);
		return (1);
	}
	else if (ft_strcmp(cmd[0], "env"))
	{
		ft_env(info->head_env, info->utils->cmd, info);
		return (1);
	}
	else
	{
		if (check_builtin_2(info, cmd))
			return (1);
	}
	return (0);
}

t_sys_err	execute_cmd(t_info *info, int cdt)
{
	int	id;

	if (cdt && check_builtin(info, info->utils->cmd))
		return (SYS_SUCCESS);
	*(sig_varible()) = true;
	id = fork();
	if (id == -1)
		return (SYS_FAIL);
	if (!id)
	{
		signal(SIGQUIT, SIG_DFL);
		if (info->utils->child && info->utils->npi != -1)
			ft_close(info->utils->copy);
		ft_close(info->fd_in);
		ft_close(info->fd_out);
		if (!cdt && check_builtin(info, info->utils->cmd))
			return (SYS_SUCCESS);
		check_access(info);
		if (execve(info->utils->exc, info->utils->cmd, info->env) == -1)
			check_which_msg(info->utils->cmd[0], info);
	}
	info->utils->id = id;
	return (SYS_SUCCESS);
}
