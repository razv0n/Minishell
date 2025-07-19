/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chng_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:40:36 by mfahmi            #+#    #+#             */
/*   Updated: 2025/07/16 10:08:07 by mfahmi           ###   ########.fr       */
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

	if (!head_exp)
		return ;
	tmp = head_exp;
	ptr = NULL;
	oldpwd = ft_strjoin("OLDPWD=", old, FIRST_P);
	pwd = ft_strjoin("PWD=", new, FIRST_P);
	if (where_to_edit(&tmp, &ptr, "OLDPWD=") == -1)
		tmp->str = join_str("declare -x ", oldpwd, 1, NULL);
	if (where_to_edit(&tmp, &ptr, "PWD=") == -1)
		tmp->str = join_str("declare -x ", pwd, 1, NULL);
	edit_env(head_env, pwd, oldpwd);
}

void	ft_cd_2(t_info *info, char *old)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, 4096);
	add_ptr(pwd, return_ptr(), FIRST_P, FREE);
	if (!old || !pwd)
	{
		perror("Minishell ");
		*(exit_status_nm()) = 0;
		if (info->utils->child)
			ft_free_all(NORMAL, 0);
		return ;
	}
	info->cw = pwd;
	edit_export(info->head_export, info->head_env, pwd, old);
	free(old);
	*(exit_status_nm()) = 0;
	if (info->utils->child)
		ft_free_all(NORMAL, 0);
}

void	exit_from_func(int ext, bool child)
{
	*(exit_status_nm()) = ext;
	if (child)
		ft_free_all(NORMAL, ext);
}

void	ft_cd(t_info *info, char **arg)
{
	char	*old;

	old = NULL;
	if (!arg[1])
		return (exit_from_func(0, info->utils->child));
	if (arg[2])
	{
		ft_putstr_fd("cd : too many arguments\n", 2);
		return (exit_from_func(1, info->utils->child));
	}
	old = getcwd(old, 4096);
	if (chdir(arg[1]) == -1)
	{
		ft_putstr_fd(ft_strjoin("cd: ", arg[1], SECOUND_P), 2);
		perror(" ");
		if (old)
			free(old);
		exit_from_func(1, info->utils->child)
		return ;
	}
	ft_cd_2(info, old);
}
