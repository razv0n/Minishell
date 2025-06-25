/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:38:05 by mfahmi            #+#    #+#             */
/*   Updated: 2025/06/22 17:04:31 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void	child_herdoc(t_info *info, t_type_word is_quotes, int fd, char *str)
{
	char	*line;

	signal(SIGINT, SIG_DFL);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, str) == 1)
		{
			free(line);
			break ;
		}
		if (ft_strchr(line, '$') && is_quotes != DOUBLE_Q
			&& is_quotes != SINGLE_Q)
			expand_2(&line, 1337, info);
		if (line && line[0])
			add_history(line);
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
	}
	ft_close(fd);
	ft_close(info->fd_in);
	ft_close(info->fd_out);
	ft_free_all(NORMAL, 0);
}

void	herdoc(char *str, t_info *info, t_type_word is_quotes)
{
	char		*line;
	pid_t		id;
	int			fd;
	static int	i;

	if (info->ext != 130)
	{
		*(sig_varible()) = true;
		fd = ft_open(info->path_name[i], O_CREAT | O_RDWR, 0766);
		ft_dupX(info->fd_in, 0, true);
		ft_dupX(info->fd_out, 1, true);
		id = fork();
		if (id == -1)
			ft_free_all(NORMAL, 5);
		else if (id == 0)
			child_herdoc(info, is_quotes, fd, str);
		waitpid(id, &info->ext, 0);
		ft_close(fd);
		exit_status(info);
	}
	if (++i >= info->count_herdoc)
		i = 0;
}

void	redirection(t_list *node, int cdt, t_info *info)
{
	// if (cdt == AMBIGUOUS)
	// {
	// 	get_next_cmd(node);
	// 	info->utils->cmd[0] = NULL;
	// 	printf("cmd [0] in %s\n", info->utils->cmd[0]);
	// }
	if (cdt == APPEND)
		rdr_append(node->content);
	else if (cdt == REDIRECT_IN)
		rdr_in(node->content, info);
	else if (cdt == HEREDOC)
		rdr_herdoc(info);
	else if (cdt == REDIRECT_OUT)
		rdr_out(node->content);
}
