/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chng_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:40:36 by mfahmi            #+#    #+#             */
/*   Updated: 2025/06/14 22:04:26 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void	edit_env(t_list *head, char *pwd, char *oldpwd)
{
	// static bool	alloc;

	// printf("oldPWD : %s\n",oldpwd);
	// printf("PWD : %s\n",pwd);
	while (head)
	{
		if (compare(head->content, pwd, 1) == 200)
		{
			// if (alloc)
			// 	free (head->content);
			// printf("PWD : %s\n",pwd);

			head->content = pwd;
		}
		if (compare(head->content, oldpwd, 1) == 200) // the result was 200 :>
		{
			// if (alloc)
				// free (head->content);
			// printf("oldPWD : %s\n",oldpwd);
			head->content = oldpwd;
		}
		head = head->next;
	}
	// alloc = true;
}

void	edit_export(t_xp *head_exp, t_list *head_env, char *new, char *old)
{
	char	*pwd;
	char	*oldpwd;
	t_xp	*tmp;
	t_xp	*ptr;

	tmp = head_exp;
	ptr = NULL;
	oldpwd = ft_strjoin("OLDPWD=", old, FIRST_P);
	pwd = ft_strjoin("PWD=", new, FIRST_P);
	where_to_edit(&tmp, &ptr, "OLDPWD=");
	// free (tmp->str);
	tmp->str = join_str("declare -x ", oldpwd, 1, NULL);
	// if (!tmp->str)
	// 	return ; //malloc
	where_to_edit(&tmp, &ptr, "PWD=");
	// free (tmp->str);
	tmp->str = join_str("declare -x ", pwd, 1, NULL);
	// if (!tmp->str)
	// 	return ; //malloc
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
			ft_free_all(NORMAL, 1);
		return ;
	}
	pwd = getcwd(pwd, 4096);
	edit_export(info->head_export, info->head_env, pwd, old);
	free (pwd);
	free (old);
	info->ext = 0;
	if (info->utils->child)
		ft_free_all(NORMAL, 1);
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
