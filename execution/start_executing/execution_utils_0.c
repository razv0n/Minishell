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
	utils->bin = false;
	if (utils->fail != -1)
	{
		if (!utils->child)
		{
			if (check_builtin(info, info->utils->cmd))
				return ;
		}
		if (check_access(info))
		{
				if (utils->child)
					execute_cmd(info, 0);
				else
					execute_cmd(info, 1);
				utils->bin = true;
		}
	}
	utils->fail = 0;
	info->permi = false;
	ft_close(1);
}

void	open_pipe(t_u *utils)
{
	if (utils->i)
	{
		ft_dupX(utils->copy, 0, true);
		ft_close (utils->copy);
	}
	if (utils->npi)
	{
		ft_pipe(utils->pi);
		ft_dupX(utils->pi[1], 1, true);
		utils->copy = ft_dupX(utils->pi[0], -1, false);
		utils->i = true; // bool //?
		ft_close (utils->pi[0]);
		ft_close (utils->pi[1]);
	}
	utils->npi--;
}

void	back_to_normal(t_info *info)
{
	if (info->utils->exc)
		info->utils->exc = NULL;
	if (info->utils->npi == -1)
		ft_dupX(info->fd_in, 0, true);
	ft_dupX(info->fd_out, 1, true);
}

void	get_next_cmd(t_info *info, t_list **head, char *file)
{
	while (*head)
	{
		if ((*head)->next && (*head)->next->type == PIPE)
			break ;
		*head = (*head)->next;
	}
	info->utils->cmd[0] = NULL;
	ft_putstr_fd("ambiguous redirect\n", 2);
}

void	start_executing(t_info *info, t_list *head, t_u *utils)
{
	while (head)
	{
		utils->cmd = collecte_cmds(head, utils);
		open_pipe(utils);
		while (head && (head->type != PIPE))
		{
			if (head->type == AMBIGUOUS)
				get_next_cmd(info, &head, head->content);
			else if (head->type != WORD)
				redirection(head, head->type, info);
			if (head)
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
	if (utils->bin)
		exit_status(info);
	if (info->path_name)
		unlink_path(info);
}

void	init_things(t_info *info, t_list *head)
{
	info->utils = ft_calloc(sizeof(t_u), 1); //! 
	info->utils->cmd = NULL; // the command //!
	info->utils->exc = NULL;
	info->utils->copy = 0;
	info->utils->i = false;
	info->utils->bin = false;
	info->utils->id = 0;
	info->utils->fail = 0;
	info->permi = false; // don't know if we will use it
	info->utils->npi = count_pipes(head);
	info->utils->child = false;
	// info->fd_in = dup(0); // 3
	// info->fd_out = dup(1); // 4
	if (info->utils->npi)
		info->utils->child = true;
	info->utils->path = update_path(ft_getenv("PATH", info->head_env)); //!
	start_executing(info, head, info->utils);
	ft_close (info->fd_in);
	ft_close (info->fd_out);
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
