/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   absolute_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yezzemry <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:26:05 by yezzemry          #+#    #+#             */
/*   Updated: 2025/04/23 10:27:22 by yezzemry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
void	redirection(char *str, int cdt);
char	**ft_split(char const *s, char c, char a);

void	free_all(char **path)
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

int	length(const char *s)
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
	int		i;
	int		j;
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
	free (s1);
	return (p);
}

char	**update_path(char *s)
{
	char	**path;
	int	i;

	if (!s)
		return (NULL);
	path = ft_split(s, ':', ' ');
	if (!path)
		return (NULL);
	i = 0;
	while (path[i])
	{
		path[i] = add_string(path[i], "/");
		if (!path[i])
			free_all(path);
		i++;
	}
	return (path);
}

int	*count_pipes(t_list *head)
{
	int	i;
	int	*pi;

	i = 0;
	while (head)
	{
		if (head->type == TYPE_PIPE)
			i++;
		head = head->next;
	}
	if (i)
	{
		pi = malloc(sizeof(int) * (i * 2));
		if (!pi)
			return (NULL);
		return (pi);
	}
	return (NULL);
}

char	**collecte_cmds(t_list *head, t_u *utils)
{
	int	i;
	t_list	*tmp;
	char 	**cmd;

	i = 0;
	tmp = head;
	while (head && (head->type != TYPE_PIPE))
	{
		if (head->type == TYPE_WORD)
			i++;
		head = head->next;
	}
	cmd = malloc(sizeof(char *) * ++i);
	if (!cmd)
		return (NULL);
	i = 0;
	head = tmp;
	while (head && (head->type != TYPE_PIPE))
	{
		if (head->type == TYPE_WORD)
			cmd[i++] = head->content;
		head = head->next;
	}
	cmd[i] = NULL;
	return (cmd);
}

int	check_access(t_u *utils)
{
	int	i;
	char	*x;

	i = 0;
	while (utils->path[i])
	{
		x = add_string(utils->path[i], utils->cmd[0]);
		if (!x)
			return (0);
		if (!access(x, F_OK))
		{
			if (!access(x, X_OK))
			{
				utils->exc = x;
				return (1);
			}
		}
		free (x);
		i++;
	}
	return (0);
}

void	get_path(t_u *utils)
{
	int	id;

	if (check_access(utils))
		utils->y = 1;
	id = fork();
	if (id == -1)
		return ;
	if (!id)
	{
		if (utils->y)
		{
			if (execve(utils->exc, utils->cmd, NULL) == -1)
			printf("execve failed\n");
		}
		else
		{
			if (execve(utils->cmd[0], utils->cmd, NULL) == -1)
				printf("execve failed\n");
		}
	}
	waitpid(id, NULL, 0);
}

void	open_pipes(t_u *utils)
{
	
}

void	start_executing(t_list **head, t_u *utils)
{
	int	i;
	t_list	*tmp;

	i = 0;
	tmp = *head;
	while (*head)
	{
		utils->cmd = collecte_cmds(*head, utils);
		if (!utils->cmd)
			return ;
		while ((*head) && ((*head)->type != TYPE_PIPE))
		{
			if ((*head)->type == TYPE_PIPE)
				open_pipe(utils);
			else if (!((*head)->type == TYPE_WORD))
				redirection((*head)->content, (*head)->type);
			*head = (*head)->next;
		}
		get_path(utils);
		free (utils->cmd);
		// back_to_normal(utils);
		if (*head)
			*head = (*head)->next;
	}
}

void	init_things(t_list **head, t_u *utils)
{
	utils->cmd = NULL;
	utils->exc = NULL;
	utils->y = 0;
	utils->pi = count_pipes(*head);
	utils->fd_in = dup(0);
	utils->fd_out = dup(1);
	utils->path = update_path(getenv("PATH"));
	if (!utils->path || utils->fd_in == -1 || utils->fd_out == -1)
		return ;
	start_executing(head, utils);
}

int	main()
{
	t_u	*utils = malloc(sizeof(t_u));
	t_list	*head = NULL;
	t_list	*node1 = malloc(sizeof(t_list));
	t_list	*node2 = malloc(sizeof(t_list));
	t_list	*node3 = malloc(sizeof(t_list));
	// t_list	*node4 = malloc(sizeof(t_list));
	// t_list	*node5 = malloc(sizeof(t_list));
	// t_list	*node6 = malloc(sizeof(t_list));
	if (!node1 || !node2 || !node3)
		return (1);

	head = node1;
	node1->content = "ls";
	node1->prev = NULL;
	node1->type = TYPE_WORD;
	node1->next = node2;

	node2->content = "test";
	node2->prev = node1;
	node2->type = TYPE_REDIRECT_OUT;
	node2->next = node3;

	node3->content = "-a";
	node3->prev = node2;
	node3->type = TYPE_WORD;
	node3->next = NULL;

	// node4->content = "|";
	// node4->prev = node3;
	// node4->type = TYPE_PIPE;
	// node4->next = NULL;

	// node5->content = "cat";
	// node5->prev = node4;
	// node5->type = TYPE_WORD;
	// node5->next = node6;

	// node6->content = "-e";
	// node6->prev = node5;
	// node6->type = TYPE_WORD;
	// node6->next = NULL;

	init_things(&head, utils);

	free (utils);
	free (node1);
	free (node2);
	free (node3);
	// free (node4);
	// free (node5);
	// free (node6);
}

// ls > test -a | cat -e

// 0 in
// 1 out
// 2 err
// 3 save in
// 4 save out

// open
// dup2
// close