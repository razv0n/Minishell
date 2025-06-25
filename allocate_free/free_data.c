/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:23:12 by mfahmi            #+#    #+#             */
/*   Updated: 2025/06/22 12:11:58 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void	ft_perror(t_error_type msg)
{
	if (msg == ERR_MALLOC)
		ft_putstr_fd("Minishell : Memory allocation failed\n", 2);
	else if (msg == EXIT)
		ft_putstr_fd("exit\n", 2);
	else if (msg == SYNTAX_ERROR)
		ft_putstr_fd("Minishell : \033[31msyntax error\033[0m\n", 2);
	else if (msg == AMBIGUOUS)
		ft_putstr_fd("Minishell : \033[31mambiguous redirect\033[0m\n", 2);
	else if (msg == ERR_EXECVE)
		ft_putstr_fd("Minishell : execve failed: ",2);
	else if (msg == SYSCALL)
		perror("Minishell");
}

void	ft_free(t_info *info, t_error_type msg)
{
	t_ptr	**head;
	t_ptr	*help;
	t_ptr	*next;

	head = return_ptr();
	help = *head;
	while (help)
	{
		if (help->place == SECOUND_P)
		{
			next = help->next;
			if (help->type == CLOSE && *(int * )help->content != -2)
				ft_close (*((int *)help->content));
			remove_node_single(head, help);
			help = next;
		}
		else
			help = help->next;
	}
	ft_perror(msg);
}

void	ft_free_all(t_error_type msg, unsigned char exit_code)
{
	t_ptr	**head;

	head = return_ptr();
	ft_lstclear_not(head);
	rl_clear_history();
	ft_perror(msg);
	exit(exit_code);
}

void	check_which_msg(char *cmd)
{
	ft_putstr_fd("Minishell: ", 2);	
	ft_putstr_fd(cmd, 2);
	// if (*permi)
	// {
	// 	ft_putstr_fd(": Permission denied\n", 2);
	// 	// *permi = false;
	// 	ft_free_all(NORMAL, 126);
	// }
	if(errno == ENOENT)
	{
		ft_putstr_fd(": Command not found\n",2);
		ft_free_all(NORMAL, 127);
	}
	// else
	// 	ft_free_all(NORMAL, 126);

	perror(" ");
	// if (errno == EACCES)
	// else
	// 	perror("execve");
	// ft_free_all(NORMAL, 1);
}

// void	free_ptr(t _ptr **head)
// {
// 	t_ptr *temp;

// 	while (*head)
// 	{
// 		temp = *head;
// 		*head = (*head)->next;
// 		free(temp->content);
// 		free(temp);
// 	}
// 	*head = NULL;
// }
