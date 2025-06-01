/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:38:05 by mfahmi            #+#    #+#             */
/*   Updated: 2025/06/01 15:36:36 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

char	*generate_name()
{
	int	fd;
	char buffer[13];
	int i;
	char *path_name;	
	char *tmp;

	i  = 0;
	fd = open("/dev/random", O_CREAT | O_RDWR);
	if (fd == -1)
		exit(1);
	read(fd ,buffer, 12);
	buffer[12] = 0;
	while (i < 13)
	{
		if(!ft_isprint(buffer[i]))
			buffer[i] = 'a' + (buffer[i] % 26);
		i++;
	}
	path_name = ft_strdup(buffer);
	tmp = path_name;
	path_name = ft_strjoin("/tmp/", path_name);
	free(tmp);
	// printf("%s\n",path_name);
	return (path_name);
}
void	path(t_info *info)
{
	int i;

	i = 0;
	info->path_name = ft_calloc(sizeof(char *), info->count_herdoc + 1);
	while(i < info->count_herdoc)
	{
		info->path_name[i] = generate_name();
		i++;
	}
	info->path_name[i] = NULL;
}

void	herdoc(char *str , t_info *info, bool is_quotes)
{
    char	*line;
    pid_t	id;
	int		fd;
	static int i;

	if (info->ext != 130)
	{
		fd =  open(info->path_name[i], O_CREAT | O_RDWR, 0766);
		if (fd == -1 || dup2(info->fd_in, 0) == -1 ||  dup2(info->fd_out, 1) == -1)
			exit(1); // should free
		id = fork();
		if (id == -1)
			exit(1);
		else if (id == 0)
		{
			signal(SIGINT, SIG_DFL);
			while (1)
			{
				line = readline("> ");
				if (!line || ft_strcmp(line, str) == 1)
				{
					free(line);
					break ;
				}
				if (ft_strchr(line, '$') && !is_quotes)
					expand_2(&line, 1337, info);
				if (line[0])
					add_history(line);
				ft_putstr_fd(line, fd);
				ft_putstr_fd("\n", fd);
				free(line);
			}
			close(fd);
			exit(1);
		}
		waitpid(id, &info->ext ,0);
		close(fd);
		exit_status(info);
	}
	i++;
	if (i == info->count_herdoc)
		i = 0;
}

void	redirection(t_list *node, int cdt, t_info *info)
{
	int	fd;
	static int i;

	if (cdt == APPEND)
	{
		fd = open(node->content, O_CREAT | O_APPEND | O_RDWR, 0766);
		if (fd == -1 || dup2(fd, 1) == -1)
			exit(5);
		close (fd);
	}
	else if (cdt == REDIRECT_IN)
	{
		if (access(node->content, F_OK) == -1)
			ft_putstr_fd("minishell: No such file or directory\n", 2); // u should specify the name of the file
		else
		{
			fd = open(node->content, O_RDONLY, 0766);
			if (fd == -1 || dup2(fd, 0) == -1)
				exit(6);
			close (fd);
		}
	}
	else if(cdt == HEREDOC)
	{
		fd = open(info->path_name[i], O_RDWR, 0766);
		if (fd == -1 || dup2(fd, 0) == -1)
			exit(8);
		close(fd);
	}
	else if (cdt == REDIRECT_OUT)
	{
		fd = open(node->content, O_CREAT | O_TRUNC | O_RDWR, 0766);
		if (fd == -1 || dup2(fd, 1) == -1)
			exit(7);
		close (fd);
	}
	i++;
	if (i == info->count_herdoc)
		i = 0;
}
