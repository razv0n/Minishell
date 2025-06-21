/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:35:37 by yezzemry          #+#    #+#             */
/*   Updated: 2025/06/21 12:19:33 by mfahmi           ###   ########.fr       */
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

int	check_access(t_info *info)
{
	int		i;
	char	*x;
	struct stat sb;

	i = 0;
	if (!info->utils->cmd[0])
		return (0);
	while (info->utils->path && info->utils->path[i])
	{
		x = add_string(info->utils->path[i], info->utils->cmd[0]);
		stat(x, &sb);
		if (!access(x, F_OK) && !S_ISDIR(sb.st_mode))
		{
			if (!access(x, X_OK))
			{
				info->utils->bin = true;
				*(sig_varible()) = true;
				info->utils->exc = x;
				return (1);
			}
		}
		i++;
	}
	return (1);
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

bool	check_lf_file(t_info *info)
{
	struct	stat st;
	
	stat(info->utils->cmd[0], &st);
	if (!access(info->utils->cmd[0], F_OK) && ft_strchr(info->utils->cmd[0], '/') && !S_ISDIR(st.st_mode))
	{
		if (!access(info->utils->cmd[0], X_OK))
			*(sig_varible()) = true;
		info->utils->exc = info->utils->cmd[0];
		return (true);
	}
	errno = ENOENT;
	return (false);
}

void	execute_cmd(t_info *info, int cdt)
{
	int	id;

	if (cdt && check_builtin(info, info->utils->cmd))
		return ;
	id = fork();
	if (id == -1)
		ft_free_all(NORMAL, 5);
	if (!id)
	{
		ft_close(info->fd_in);
		ft_close(info->fd_out);
		if (info->utils->child)
			ft_close (info->utils->copy);
		if (!cdt && check_builtin(info, info->utils->cmd))
			return ;
		if ((!info->utils->bin && !check_lf_file(info)) || execve(info->utils->exc, info->utils->cmd, info->env) == -1)
		{ 
			ft_putstr_fd("Minishell: " ,2);
			ft_putstr_fd(info->utils->cmd[0] ,2);
			if (errno == EACCES)
				perror(" :");
			else if (errno == ENOENT)
				ft_putstr_fd(" :command not found\n", 2);
			else
				perror("execve");
		} 
	}
	info->utils->id = id;
}
