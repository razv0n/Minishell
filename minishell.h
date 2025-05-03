/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yezzemry <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:38:43 by yezzemry          #+#    #+#             */
/*   Updated: 2025/04/14 10:40:53 by yezzemry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# include <sys/wait.h>

enum e_type
{
    TYPE_WORD,
    TYPE_PIPE,
    TYPE_REDIRECT_IN,
    TYPE_REDIRECT_OUT,
    TYPE_HEREDOC,
    TYPE_APPEND,
};

typedef struct utils
{
	char	**path;
	char	**cmd;
	char	*exc;
	int	check;
	int	copy;
	int	npi;
	int	pi[2];
	int	fd_in;
	int	fd_out;
}	t_u;

typedef struct export
{
	char *str;
	struct export *next;
}	xp;

typedef struct t_node
{
	char	*content;
	int	type;
	struct	t_node *next;
	struct	t_node *prev;
}	t_list;

#endif
