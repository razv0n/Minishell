/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:26:05 by yezzemry          #+#    #+#             */
/*   Updated: 2025/06/14 15:57:27 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

// void	free_double(char **str) // pls change the name of it
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		free (str[i]);
// 		i++;
// 	}
// 	free (str);
// }

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

// char	*joined_for_herdoc(t_list *head, bool *is_quotes)
// {
// 	char	*str;
// 	char	*str_1;

// 	str = ft_strdup(head->content);
// 	if (check_quotes(str[0]))
// 	{
// 		remove_quotes(&str, head);
// 		*is_quotes = true;
// 	}
// 	while (head)
// 	{
// 		if (head->joined)
// 		{
// 			str_1 = ft_strdup(head->next->content);
// 			if (check_quotes(str_1[0]))
// 			{
// 				remove_quotes(&str_1, head->next);
// 				*is_quotes = true;
// 			}
// 			str = ft_strjoin(str, str_1);
// 		}
// 		else
// 			break ;
// 		head = head->next;
// 	}
// 	return (str);
// }
char	*generate_name(void)
{
	int		fd;
	char	buffer[13];
	int		i;
	char	*path_name;

	i = 0;
	fd = open("/dev/random", O_CREAT | O_RDWR);
	if (fd == -1)
		exit(1);
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
	return (path_name);
}

void	start_herdoc(t_info *info, t_list *head)
{
	char	*str;
	bool	is_quotes;

	is_quotes = false;
	info->count_herdoc = count_herdoc(head);
	path(info);
	while (head)
	{
		if (head->type == HEREDOC)
		{
			// str = joined_for_herdoc(head->next, &is_quotes);
			herdoc(head->content, info, head->quotes_type);
			// free(str);
		}
		head = head->next;
	}
}

void	unlink_path(t_info *info)
{
	int	i;

	i = 0;
	while (info->path_name[i])
	{
		unlink(info->path_name[i]);
		i++;
	}
}

void	path(t_info *info)
{
	int	i;

	i = 0;
	info->path_name = ft_calloc(sizeof(char *), info->count_herdoc + 1);
	while (i < info->count_herdoc)
	{
		info->path_name[i] = generate_name();
		i++;
	}
	info->path_name[i] = NULL;
}
