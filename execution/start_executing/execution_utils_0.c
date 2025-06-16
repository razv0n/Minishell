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

void	get_path(t_info *info, t_u *utils)
{
	if (utils->fail != -1)
	{
		if (!utils->child)
		{
			if (check_builtin(info, info->utils->cmd))
			    return ;
		}
		if (check_access(info) || info->permi == true)
		{
			if (utils->child)
				execute_cmd(info, 0);
			else
				execute_cmd(info, 1);
			utils->bin = true;
		}
		else
		{
				ft_putstr_fd(info->utils->cmd[0], 2);
				ft_putstr_fd(": Command not found\n",2);
				info->ext = 127;
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
			ft_free_all(NORMAL, 4);
		close (utils->copy);
	}
	if (utils->npi)
	{
		if (pipe(utils->pi) == -1)
			ft_free_all(NORMAL, 4);
		if (dup2(utils->pi[1], 1) == -1)
			ft_free_all(NORMAL, 4);
		utils->copy = dup(utils->pi[0]);
		if (utils->copy == -1 )
			ft_free_all(NORMAL, 4);
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
		// free (info->utils->exc);
		info->utils->exc = NULL;
	}
	if (!info->utils->npi)
	{
		if (dup2(info->fd_in, 0) == -1)
			ft_free_all(NORMAL, 4);
	}
	if (dup2(info->fd_out, 1) == -1)
		ft_free_all(NORMAL, 4);
}

void	start_executing(t_info *info, t_list *head, t_u *utils)
{
	while (head)
	{
		utils->bin = false;
		utils->cmd = collecte_cmds(head, utils);
		open_pipe(utils);
		while (head && (head->type != PIPE))
		{
			if (head->type != WORD)
				redirection(head, head->type, info);
			head = head->next;
		}
		get_path(info, utils);
		back_to_normal(info);
		if (head)
			head = head->next;
	}
	if (info->ext != 127)
    	waitpid(utils->id, &info->ext, WUNTRACED);
	while (wait(NULL) != -1)
		;
	if (info->utils->bin)
		exit_status(info);
	if (info->path_name)
		unlink_path(info);
}

void	init_things(t_info *info, t_list *head)
{
	info->utils = ft_calloc (sizeof(t_u), 1); //! 
	info->utils->cmd = NULL; // the command //!
	info->utils->exc = NULL;
	info->utils->copy = 0;
	info->utils->i = 0;
	info->utils->bin = false;
	info->utils->id = 0;
	info->utils->fail = 0;
	info->permi = false;
	info->utils->npi = count_pipes(head);
	info->utils->child = false;
	if (info->utils->npi)
		info->utils->child = true;
	info->fd_in = dup(0);
	info->fd_out = dup(1);
	info->utils->path = update_path(ft_getenv("PATH", info->head_env)); //!
	if (info->fd_in == -1
		|| info->fd_out == -1)
		ft_free_all(NORMAL, 4);
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
