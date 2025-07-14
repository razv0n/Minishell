/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:23:12 by mfahmi            #+#    #+#             */
/*   Updated: 2025/07/14 17:52:42 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void	ft_perror(t_error_type msg)
{
	if (msg == ERR_MALLOC)
		ft_putstr_fd("Minishell : Memory allocation failed\n", 2);
	else if (msg == EXIT)
		ft_putstr_fd("exit\n", 2);
	else if (msg == HERE_DOCUMENT)
		ft_putstr_fd("Minishell : maximum here-document count exceeded\n", 2);
	else if (msg == SYNTAX_ERROR)
		ft_putstr_fd("Minishell : \033[31msyntax error\033[0m\n", 2);
	else if (msg == ERR_AMBIGUOUS)
		ft_putstr_fd("Minishell : \033[31mambiguous redirect\033[0m\n", 2);
	else if (msg == ERR_EXECVE)
		ft_putstr_fd("Minishell : execve failed: ", 2);
	else if (msg == SYSCALL)
		perror(" ");
}

void	ft_free(t_error_type msg)
{
	t_ptr	**head;
	t_ptr	*help;
	t_ptr	*next;

	head = return_ptr();
	if (!head)
		return ;
	help = *head;
	while (help)
	{
		if (help->place == SECOUND_P)
		{
			next = help->next;
			if (help->type == UNLINK)
				unlink_path((char **)help->content);
			else if (help->type == CLOSE && *(int *)help->content != -2)
				ft_close(*((int *)help->content));
			remove_node_single(head, help);
			help = next;
		}
		else
			help = help->next;
	}
	ft_perror(msg);
}

void	ft_free_all(t_error_type msg, int exit_code)
{
	t_ptr	**head;

	head = return_ptr();
	if (msg == CHILD)
		ft_lstclear_not(head, true);
	else
		ft_lstclear_not(head, false);
	rl_clear_history();
	ft_perror(msg);
	exit(exit_code);
}

void	check_which_msg(char *cmd, t_info *info)
{
	if (info->permi == true)
		errno = EACCES;
	else if (info->utils->error == 1)
	{
		ft_putstr_fd(ft_strjoin(cmd, ": Command not found\n", SECOUND_P), 2);
		ft_free_all(NORMAL, 127);
	}
	ft_putstr_fd(cmd, 2);
	perror(" ");
	if (errno == ENOENT)
		ft_free_all(NORMAL, 127);
	ft_free_all(NORMAL, 126);
}
