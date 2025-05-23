/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_executing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:26:05 by yezzemry          #+#    #+#             */
/*   Updated: 2025/05/20 11:24:02 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void	free_path(char **path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		free (path[i]);
		i++;
	}
	free (path);
}

int	length(char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*add_string(char *s1, char *s2)
{
	int			i;
	int			j;
	char		*p;

	i = length(s1) + length(s2);
	p = malloc(sizeof(char) * (i + 1));
	if (p == NULL || s1 == NULL || s2 == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		p[i] = s2[j];
		i++;
		j++;
	}
	p[i] = '\0';
	// free (s1);
	return (p);
}

char	**update_path(char *s)
{
	char	**path;
	int	i;
	char *tmp;

	if (!s)
		return (NULL);
	path = ft_split(s, ':');
	if (!path)
		return (NULL);
	i = 0;
	while (path[i])
	{
		tmp = path[i];
		path[i] = add_string(path[i], "/");
		free(tmp);
		if (!path[i])
			free_path(path);
		i++;
	}
	return (path);
}

int	count_pipes(t_list *head)
{
	int	i;

	i = 0;
	while (head)
	{
		if (head->type == PIPE)
			i++;
		head = head->next;
	}
	return (i);
}

char	**collecte_cmds(t_list *head, t_u *utils)
{
	int	i;
	t_list	*tmp;
	char 	**cmd;

	i = 0;
	tmp = head;
	while (head && (head->type != PIPE))
	{
		if (head->type == WORD)
			i++;
		head = head->next;
	}
	cmd = malloc (sizeof(char *) * ++i);
	if (!cmd)
		return (NULL);
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
	int	i;
	char	*x;

	i = 0;
	while (info->utils->path[i])
	{
		x = add_string(info->utils->path[i], info->utils->cmd[0]);
		if (!x)
			return(0); // handle this error
		if (!access(x, F_OK))
		{
			if (!access(x, X_OK))
			{
				info->utils->exc = x;
				return (1);
			}
			else
				info->ext = 126;
		}
		free (x);
		i++;
	}
	return (1);
}
 
// void	close_fds(int id)
// {
	// if (!i)
	// {
	// if (id)
	// 	close (1);
	// }
	// else
	// {
	// 	if (!id)
	// 	{
	// 		if (npi)
	// 			close (1);
	// 	}
	// 	else
	// 	{
	// 		if (npi)
	// 			close (0);
	// 	}
	// }
// }

int	check_builtin_2(t_info *info, char **cmd)
{
	if (ft_strcmp(cmd[0], "pwd"))
	{
		ft_pwd();
		return (1);
	}
	if (ft_strcmp(cmd[0], "cd"))
	{
		ft_cd(info, cmd);
		return (1);
	}
	else if (ft_strcmp(cmd[0], "echo"))
	{
		ft_echo(cmd);
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
		ft_env(info->head_env, info->utils->cmd);
		return (1);
	}
	else
	{
		if (check_builtin_2(info, cmd)) // i commented this for not showing the error
			return (1);
	}
	return (0);
}

void	execute_cmd(t_info *info, int cdt, int *wt, int *i)
{
	int	id;

	if (cdt)
	{
		if (check_builtin(info, info->utils->cmd))
			return ;
	}
	id = fork();
	if (id == -1)
		exit(8);
	if (!id)
	{
		if (!cdt)
		{
			if (check_builtin(info, info->utils->cmd))
				return ;
		}
		if (info->utils->exc)
			execve(info->utils->exc, info->utils->cmd, NULL);
		execve(info->utils->cmd[0], info->utils->cmd, NULL);
		write (2, info->utils->cmd[1], length(info->utils->cmd[1]));
		ft_putstr_fd(": command not found\n", 2);
		exit (127);
	}
	wt[(*i)++] = id;
}

void	get_path(t_info *info, t_u *utils, int *wt, int *i)
{
	if (check_access(info))
	{
		if (utils->child)
			execute_cmd(info, 0, wt, i);
		else
			execute_cmd(info, 1, wt, i);
	}
	if (utils->npi)
		close(1);
}

void	open_pipe(t_u *utils)
{
	static int	i;

	if (i)
	{
		if (dup2(utils->copy, 0) == -1)
			exit(5);
		close (utils->copy);
	}
	if (utils->npi)
	{
		if (pipe(utils->pi) == -1)
			exit(3); // handle pipe error
		if (dup2(utils->pi[1], 1) == -1)
			exit(4);
		utils->copy = dup(utils->pi[0]);
		i++;
		utils->npi--;
		close (utils->pi[0]);
		close (utils->pi[1]);
	}
}

void	back_to_normal(t_u *utils)
{
	if (utils->exc)
	{
		free (utils->exc);
		utils->exc = NULL;
	}
	if (!utils->npi)
	{
		if (dup2(utils->fd_in, 0) == -1)
			exit(10);
	}
	if (dup2(utils->fd_out, 1) == -1)
		exit(11);
}

void	start_executing(t_info *info, t_list *head, t_u *utils)
{
	int	wt[utils->npi + 1];
	int	i;

	i = 0;
	ft_bzero(wt, sizeof(int) * (utils->npi + 1));
	while (head)
	{
		utils->cmd = collecte_cmds(head, utils);
		if (!utils->cmd)
			exit(2); // handle malloc or other things errors
		open_pipe(utils);
		while (head && (head->type != PIPE))
		{
			if (head->type != WORD)
				redirection(head->content, head->type, info);
			head = head->next;
		}
		// if (utils->str_heredoc)
			// unlink(utils->str_heredoc);
		get_path(info, utils, wt, &i);
		back_to_normal(utils);
		free (utils->cmd);
		if (head)
			head = head->next;
	}
	while (i-- >= 0)
	waitpid(wt[i + 1], &info->ext, 0);
	exit_status(info);
	printf("i : %d exit  :%d\n",i, info->ext);
}

void	init_things(t_info *info, t_list *head)
{
	info->utils = malloc (sizeof(t_u)); //! 
	if (!info->utils)
	return ; //handle error
	info->utils->cmd = NULL; // the command //!
	info->utils->exc = NULL;
	info->utils->copy = 0;
	info->ext = 0;
	info->utils->npi = count_pipes(head);
	info->utils->child = false;
	if (info->utils->npi)
		info->utils->child = true;
	info->utils->fd_in = dup(0);
	info->utils->fd_out = dup(1);
	info->utils->path = update_path(getenv("PATH")); //!
	if (!info->utils->path || info->utils->fd_in == -1 || info->utils->fd_out == -1)
		exit(1);
	start_executing(info, head, info->utils);
	close (info->utils->fd_in);
	close (info->utils->fd_out);
}

// utils->cmd = NULL;
// utils->exc = NULL;
// utils->copy = 0;
// utils->npi = count_pipes(head);
// utils->fd_in = dup(0);
// utils->fd_out = dup(1);
// utils->path = update_path(getenv("PATH"));
// if (!utils->path || utils->fd_in == -1 || utils->fd_out == -1)
// 	exit(1);
// start_executing(head, utils);

// int	main()
// {
// 	t_u	*utils =ft_mallocsizeof(t_u));
// 	t_list	*head = NULL;
// 	t_list	*node1 =ft_mallocsizeof(t_list));
// 	t_list	*node2 =ft_mallocsizeof(t_list));
// 	t_list	*node3 =ft_mallocsizeof(t_list));
// 	t_list	*node4 =ft_mallocsizeof(t_list));
// 	t_list	*node5 =ft_mallocsizeof(t_list));
// 	t_list	*node6 =ft_mallocsizeof(t_list));
// 	t_list	*node7 =ft_mallocsizeof(t_list));
// 	t_list	*node8 =ft_mallocsizeof(t_list));
// 	if (!utils || !node1 || !node2 || !node3 
// 		|| !node4 || !node5 || !node6 || !node7 || !node8)
// 		return (1);

// 	head = node1;
// 	node1->content = "sleep";
// 	node1->prev = NULL;
// 	node1->type = WORD;
// 	node1->next = node2;

// 	node2->content = "5";
// 	node2->prev = node1;
// 	node2->type = WORD;
// 	node2->next = node3;

// 	node3->content = "|";
// 	node3->prev = node2;
// 	node3->type = PIPE;
// 	node3->next = node4;

// 	node4->content = "sleep";
// 	node4->prev = node3;
// 	node4->type = WORD;
// 	node4->next = node5;

// 	node5->content = "3";
// 	node5->prev = node4;
// 	node5->type = WORD;
// 	node5->next = NULL;

// 	node6->content = "|";
// 	node6->prev = node5;
// 	node6->type = PIPE;
// 	node6->next = node7;

// 	node7->content = "wc";
// 	node7->prev = node6;
// 	node7->type = WORD;
// 	node7->next = node8;

// 	node8->content = "-l";
// 	node8->prev = node7;
// 	node8->type = WORD;
// 	node8->next = NULL;

// 	// printf("%d\n", getpid());
// 	init_things(head, utils);
// 	close (utils->fd_in);
// 	close (utils->fd_out);

// 	free (utils);
// 	free (node1);
// 	free (node2);
// 	free (node3);
// 	free (node4);
// 	free (node5);
// 	free (node6);
// 	free (node7);
// 	free (node8);
// }
