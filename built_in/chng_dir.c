/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chng_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:40:36 by mfahmi            #+#    #+#             */
/*   Updated: 2025/07/01 17:18:06 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void	edit_env(t_list *head, char *pwd, char *oldpwd)
{
	while (head)
	{
		if (compare(head->content, pwd, true, false) == 200)
			head->content = pwd;
		if (compare(head->content, oldpwd, true, false) == 200)
			head->content = oldpwd;
		head = head->next;
	}
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
	tmp->str = join_str("declare -x ", oldpwd, 1, NULL);
	where_to_edit(&tmp, &ptr, "PWD=");
	tmp->str = join_str("declare -x ", pwd, 1, NULL);
	edit_env(head_env, pwd, oldpwd);
}

void	ft_cd_2(t_info *info, char *old)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, 4096);
	if (!old || !pwd)
	{
		ft_putstr_fd("No such file or directory\n", 2);
		info->ext = 0;
		return ;
	}
	info->cw = pwd;
	add_ptr(pwd, return_ptr(), FIRST_P, FREE);
	edit_export(info->head_export, info->head_env, pwd, old);
	free(old);
	info->ext = 0;
	if (info->utils->child)
		ft_free_all(NORMAL, 0);
}

void	ft_cd(t_info *info, char **arg)
{
	char	*old;

	old = NULL;
	if (!arg[1])
		return ;
	old = getcwd(old, 4096);
	if (chdir(arg[1]) == -1)
	{
		if (arg[2])
			ft_putstr_fd("cd: too many arguments\n", 2);
		else
		{
			ft_putstr_fd(ft_strjoin("cd: ", arg[1], SECOUND_P), 2);
			perror(" ");
		}
		if (old)
			free(old);
		info->ext = 1;
		if (info->utils->child)
			ft_free_all(NORMAL, 1);
		return ;
	}
	ft_cd_2(info, old);
}
