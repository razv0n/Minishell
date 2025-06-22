/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:35:37 by yezzemry          #+#    #+#             */
/*   Updated: 2025/06/21 16:54:55 by mfahmi           ###   ########.fr       */
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
		if (info->utils->child && info->utils->npi != -1)
			ft_close (info->utils->copy);
		ft_close(info->fd_in);
		ft_close(info->fd_out);
		if (!cdt && check_builtin(info, info->utils->cmd))
			return ;
		// fprintf(stderr, "the str : %s\n", info->utils->exc);
		if ((!info->utils->bin && !check_lf_file(info))
			|| execve(info->utils->exc, info->utils->cmd, info->env) == -1)
		{
			ft_putstr_fd("Minishell: ", 2);
			ft_putstr_fd(info->utils->cmd[0], 2);
			if (errno == EACCES)
			{
				perror(": ");
				ft_free_all(NORMAL, 126);
			}
			else if(errno == ENOENT)
			{
				ft_putstr_fd(" : Command not found\n",2);
				ft_free_all(NORMAL, 127);
			}
			else
				perror("execve:");
			ft_free_all(NORMAL, 1);

		} //?
		
		// exit (127);
		// ENOENT
		// EACCES
	}
	info->utils->id = id;
}
