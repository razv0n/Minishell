/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_executing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:26:05 by yezzemry          #+#    #+#             */
/*   Updated: 2025/06/01 15:10:04 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void	free_double(char **str) // pls change the name of it 
{
	int	i;

	i = 0;
	while (str[i])
	{
		free (str[i]);
		i++;
	}
	free (str);
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
			free_double(path);
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
		if (info->utils->child)
			close(info->utils->copy);
		// fprintf(stderr, "the pid is %d \n", getpid());
		// sleep(20);	
		if (info->utils->exc)
			execve(info->utils->exc, info->utils->cmd, info->env);
		execve(info->utils->cmd[0], info->utils->cmd, info->env);
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
	if (utils->i)
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
		close (utils->pi[1]);
		close (utils->pi[0]);
		utils->i++;
		utils->npi--;
	}
}

void	back_to_normal(t_info *info)
{
	if (info->utils->exc)
	{
		free (info->utils->exc);
		info->utils->exc = NULL;
	}
	if (!info->utils->npi)
	{
		if (dup2(info->fd_in, 0) == -1)
			exit(10);
	}
	if (dup2(info->fd_out, 1) == -1)
		exit(11);
}

void	start_executing(t_info *info, t_list *head, t_u *utils)
{
	int	wt[utils->npi + 1];
	int	i;

	i = 0;
	// ft_bzero(wt, sizeof(int) * (utils->npi + 1));
	while (head)
	{
		utils->cmd = collecte_cmds(head, utils);
		if (!utils->cmd)
			exit(2); // handle malloc or other things errors
		open_pipe(utils);
		while (head && (head->type != PIPE))
		{
			if (head->type != WORD)
				redirection(head, head->type, info);
			head = head->next;
		}
		get_path(info, utils, wt, &i);
		back_to_normal(info);
		// printf("path : %s\n", info->path_name);
		free (utils->cmd);
		if (head)
			head = head->next;
	}
	waitpid(info->wt, &info->ext, 0);
	while (wait(NULL) > 0)
		;
	if (info->path_name)
		unlink_path(info); // the unlink free the info->path_name
	exit_status(info);
}

int	count_herdoc(t_list *head)
{
	int count_herdoc;
	
	count_herdoc = 0;
	while (head)
	{
		if (head->type == HEREDOC)
			count_herdoc++;
		head = head->next;
	}
	return (count_herdoc);
}

char	*joined_for_herdoc(t_list *head, bool *is_quotes)
{
	char	*str, *tmp, *str_1;
	str = ft_strdup(head->content);
	if (check_quotes(str[0]))
	{
		remove_quotes(&str, head);
		*is_quotes = true;
	}
	while (head)
	{
		if (head->joined)
		{	
			tmp = str;
			str_1 = ft_strdup(head->next->content);
			if (check_quotes(str_1[0]))
			{
				remove_quotes(&str_1, head->next);
				*is_quotes = true;
			}
			str = ft_strjoin(str, str_1);
			free(str_1);
			free(tmp);
		}
		else
			break;
		head = head->next;
	}
	return (str);
}

void	start_herdoc(t_info *info, t_list *head)
{
	char *str;
	bool is_quotes;
	
	is_quotes = false;
	info->count_herdoc = count_herdoc(head);
	path(info);
	while (head)
	{
		if (head->type == HEREDOC)
		{
			str = joined_for_herdoc(head->next, &is_quotes);
			herdoc(str, info, is_quotes);
			free(str);
		}
		head = head->next;
	}	
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
	info->wt = 0;
	info->utils->i = 0;
	info->utils->npi = count_pipes(head);
	info->utils->child = false;
	if (info->utils->npi)
		info->utils->child = true;
	info->utils->path = update_path(getenv("PATH")); //!
	if (!info->utils->path)
		exit(1);
	start_executing(info, head, info->utils);
	close (info->fd_in);
	close (info->fd_out);
}
void	unlink_path (t_info *info)
{
	int i;
	
	i = 0;
	while(info->path_name[i])
	{
		unlink(info->path_name[i]);
		i++;
	}
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
