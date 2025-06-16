/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_0.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:26:05 by yezzemry          #+#    #+#             */
/*   Updated: 2025/06/01 21:22:21 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

void	get_path(t_info *info, t_u *utils)
{
	if (utils->fail != -1)
	{
		if (check_access(info))
		{
			if (utils->child)
				execute_cmd(info, 0);
			else
				execute_cmd(info, 1);
			utils->bin = 1;
		}
	}
	utils->fail = 0;
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
		utils->i++;
		utils->npi--;
		close (utils->pi[0]);
		close (utils->pi[1]);
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
	while (head)
	{
		utils->cmd = collecte_cmds(head, utils);
		if (!utils->cmd)
			exit(2); // handle malloc or other things errors
		utils->bin = 0;//?
		open_pipe(utils);
		while (head && (head->type != PIPE))
		{
			if (head->type != WORD)
				redirection(head, head->type, info);
			head = head->next;
		}
		get_path(info, utils);
		back_to_normal(info);
		free (utils->cmd);
		if (head)
			head = head->next;
	}
	waitpid(utils->id, &info->ext, WUNTRACED);
	while (wait(NULL) != -1)
		;
	if (info->path_name)
		unlink_path(info);
	if (utils->bin)
		exit_status(info);
}

void	init_things(t_info *info, t_list *head)
{
	info->utils = malloc (sizeof(t_u)); //! 
	if (!info->utils)
		return ; //handle error
	info->utils->cmd = NULL; // the command //!
	info->utils->exc = NULL;
	info->utils->copy = 0;
	info->utils->i = 0;
	info->utils->id = 0;
	info->utils->fail = 0;
	info->utils->npi = count_pipes(head);
	info->utils->child = false;
	if (info->utils->npi)
		info->utils->child = true;
	info->fd_in = dup(0);
	info->fd_out = dup(1);
	info->utils->path = update_path(getenv("PATH")); //!
	if (!info->utils->path || info->fd_in == -1
		|| info->fd_out == -1)
		exit(1);
	start_executing(info, head, info->utils);
	close (info->fd_in);
	close (info->fd_out);
}

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
