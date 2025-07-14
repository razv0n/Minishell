/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:38:05 by mfahmi            #+#    #+#             */
/*   Updated: 2025/07/14 17:54:28 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void	handle_sig_init(int sig)
{
	(void)sig;
	ft_free_all(CHILD, 130);
}

void	child_herdoc(t_info *info, t_type_word is_quotes, int fd, char *str)
{
	char	*line;

	signal(SIGINT, handle_sig_init);
	while (1)
	{
		line = readline("> ");
		add_ptr(line, return_ptr(), SECOUND_P, FREE);
		if (!line || ft_strcmp(line, str) == 1)
			break ;
		if (ft_strchr(line, '$') && is_quotes != DOUBLE_Q
			&& is_quotes != SINGLE_Q)
			expand_2(&line, 1337, info);
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
	}
	ft_free_all(CHILD, 0);
}

t_sys_err	herdoc(char *str, t_info *info, t_type_word is_quotes)
{
	pid_t		id;
	int			fd;
	static int	i;

	if (!info->sigint_herdoc)
	{
		*(sig_varible()) = true;
		fd = ft_open(info->path_name[i], O_CREAT | O_RDWR, 0766);
		if (fd == SYS_FAIL)
			return (SYS_FAIL);
		id = fork();
		if (id == -1)
			return (SYS_FAIL);
		else if (id == 0)
			child_herdoc(info, is_quotes, fd, str);
		waitpid(id, &info->ext, 0);
		ft_close(fd);
		exit_status(info);
		*(sig_varible()) = false;
	}
	if (++i >= info->count_herdoc)
		i = 0;
	return (SYS_SUCCESS);
}

t_sys_err	redirection(t_list *node, int cdt, t_info *info)
{
	info->cmd_err = node->content;
	if (cdt == APPEND)
		return (rdr_append(node->content, info));
	else if (cdt == REDIRECT_IN)
		return (rdr_in(node->content, info));
	else if (cdt == HEREDOC)
		return (rdr_herdoc(info));
	else if (cdt == REDIRECT_OUT)
		return (rdr_out(node->content, info));
	return (SYS_SUCCESS);
}
