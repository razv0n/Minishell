/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:26:05 by yezzemry          #+#    #+#             */
/*   Updated: 2025/07/03 10:32:30 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int	count_herdoc(t_list *head)
{
	int	count_herdoc;

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
	char	*str;

	str = ft_strdup(head->content, SECOUND_P);
	if (check_quotes(str[0]))
	{
		remove_quotes(&str, head);
		*is_quotes = true;
	}
	while (head)
	{
		if (head->joined && head->next)
		{
			if (check_quotes(head->next->content[0]))
			{
				remove_quotes(&head->next->content, head->next);
				*is_quotes = true;
			}
			str = ft_strjoin(str, head->next->content, SECOUND_P);
		}
		else
			break ;
		head = head->next;
	}
	return (str);
}

char	*generate_name(void)
{
	int		fd;
	char	buffer[13];
	int		i;
	char	*path_name;

	i = 0;
	fd = ft_open("/dev/random", O_CREAT | O_RDWR, 0);
	if (fd == SYS_FAIL)
		return (NULL);
	read(fd, buffer, 12);
	buffer[12] = 0;
	while (i < 13)
	{
		if (!ft_isprint(buffer[i]))
			buffer[i] = 'a' + (buffer[i] % 26);
		i++;
	}
	path_name = ft_strdup(buffer, SECOUND_P);
	path_name = ft_strjoin("/tmp/", path_name, SECOUND_P);
	ft_close(fd);
	return (path_name);
}

t_sys_err	start_herdoc(t_info *info, t_list *head)
{
	char	*str;
	bool	is_quotes;

	is_quotes = false;
	info->count_herdoc = count_herdoc(head);
	if (!info->count_herdoc)
		return (SYS_SUCCESS);
	if (path(info) == SYS_FAIL)
		return (SYS_FAIL);
	while (head)
	{
		if (head->type == HEREDOC)
		{
			str = joined_for_herdoc(head, &is_quotes);
			if (herdoc(str, info, is_quotes) == SYS_FAIL)
				return (SYS_FAIL);
			if (info->ext == 130)
				info->sigint_herdoc = true; // opens file 2 run cmds
		}
		head = head->next;
	}
	return (SYS_SUCCESS);
}

void	unlink_path(char **path_name)
{
	int	i;

	i = 0;
	if (!path_name)
		return ;
	while (path_name[i])
	{
		unlink(path_name[i]);
		i++;
	}
	path_name = NULL;
}

t_sys_err	path(t_info *info)
{
	int	i;

	i = 0;
	info->path_name = ft_malloc(sizeof(char *) * (info->count_herdoc + 1), SECOUND_P, UNLINK);
	while (i < info->count_herdoc)
	{
		info->path_name[i] = generate_name();
		if (!info->path_name[i])
			return (SYS_FAIL);
		i++;
	}
	info->path_name[i] = NULL;
	return (SYS_SUCCESS);
}
