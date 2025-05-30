/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chng_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:40:36 by mfahmi            #+#    #+#             */
/*   Updated: 2025/05/08 14:40:37 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void	edit_env(t_list *head, char *pwd, char *oldpwd)
{
	static bool	alloc;

	while (head)
	{
		if (!compare(head->content, pwd, 1))
		{
			if (alloc)
				free (head->content);
			head->content = pwd;
		}
		if (!compare(head->content, oldpwd, 1))
		{
			if (alloc)
				free (head->content);
			head->content = oldpwd;
		}
		head = head->next;
	}
	alloc = true;
}

void	edit_export(xp *head_exp, t_list *head_env, char *new, char *old)
{
	char	*pwd;
	char	*oldpwd;
	xp	*tmp;
	xp	*ptr;

	tmp = head_exp;
	ptr = NULL;
	oldpwd = ft_strjoin("OLDPWD=", old);
	pwd = ft_strjoin("PWD=", new);
	if (!oldpwd || !pwd)
		return ; //malloc
	where_to_edit(&tmp, &ptr, "OLDPWD=");
	free (tmp->str);
	tmp->str = join_str("declare -x ", oldpwd);
	if (!tmp->str)
		return ; //malloc
	where_to_edit(&tmp, &ptr, "PWD=");
	free (tmp->str);
	tmp->str = join_str("declare -x ", pwd);
	if (!tmp->str)
		return ; //malloc
	edit_env(head_env, pwd, oldpwd);
}

void	ft_cd(t_info *info, char **arg)
{
	char	*pwd;
	char	*old;

	pwd = NULL;
	old = NULL;
	if (!arg[1])
		return ;
	old = getcwd(old, 4096);
	if (chdir(arg[1]) == -1)
	{
		if (arg[2])
			ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		else
		{
			ft_putstr_fd("minishell: cd: ", 2);
			ft_putstr_fd(arg[1], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
		}
		free (old);
		info->ext = 1;
		if (info->utils->child)
			exit(1);
		return ;
	}
	pwd = getcwd(pwd, 4096);
	edit_export(info->head_export, info->head_env, pwd, old);
	free (pwd);
	free (old);
	info->ext = 0;
	if (info->utils->child)
		exit(0);
}

// #include <fcntl.h>
// int	main()
// {
// 	char s[100];
// 	printf("%s\n", getcwd(s, 100));
// 	char *arg[] = {"cd", "/home/yezzemry/Desktop/youness_br", NULL};
// 	ft_cd(arg);
// 	// open("youness", O_RDONLY | O_CREAT, 0777);
// 	printf("%s\n", getcwd(s, 100));
// 	return (0);
// }
