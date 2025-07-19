/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 11:59:19 by mfahmi          	#+#    #+#            */
/*   Updated: 2025/06/17 22:15:30 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

int	parse_var(char *s)
{
	int	i;

	i = 0;
	if (!ft_isalpha(s[i]) && (s[i] != '_'))
		return (1);
	while (s[i] && (ft_isalpha(s[i]) || ft_isdigit(s[i]) || s[i] == '_')
		&& (s[i] != '='))
		i++;
	if (!s[i] || s[i] == '=')
		return (0);
	return (1);
}

int	where_to_edit(t_xp **tmp, t_xp **ptr, char *s)
{
	int	res;

	res = 0;
	while (*tmp)
	{
		res = compare((*tmp)->str + 11, s, true, true);
		if (res >= 0 && res != 200)
			return (1);
		else if (res == 200)
			return (-1);
		else if (res == -200)
			return (0);
		*ptr = *tmp;
		*tmp = (*tmp)->next;
	}
	return (1);
}

void	add_to_export_2(t_xp **head, t_xp *node, t_xp *ptr, int cdt)
{
	if (cdt == -1)
	{
		if (ptr)
			ptr->next->str = node->str;
		else
			(*head)->str = node->str;
	}
	else if (ptr)
	{
		node->next = ptr->next;
		if (ptr->next)
			ptr->next->prev = node;
		ptr->next = node;
		node->prev = ptr;
	}
	else if (!ptr)
	{
		node->next = *head;
		if (*head)
			(*head)->prev = node;
		*head = node;
	}
}

int	add_to_export(t_xp **head, char *s)
{
	t_xp	*tmp;
	t_xp	*node;
	t_xp	*ptr;
	int		cdt;
	int		equal;

	equal = 0;
	if (parse_var(s))
	{
		ft_putstr_fd(ft_strjoin(ft_strjoin("export: `", s, SECOUND_P),
				"': not a valid identifier\n", SECOUND_P), 2);
		*(exit_status_nm()) = 1;
		return (0);
	}
	tmp = *head;
	ptr = NULL;
	cdt = where_to_edit(&tmp, &ptr, s);
	node = create_node(join_str("declare -x ", s, cdt, &equal));
	if (!node)
		return (0);
	add_to_export_2(head, node, ptr, cdt);
	if (!equal)
		return (0);
	return (cdt);
}

void	create_export(t_info *info, char **env, int i)
{
	char	*tmp;
	int		j;
	int		x;

	info->head_export = NULL;
	i = 0;
	x = 0;
	while (env[i] && env[i + 1])
	{
		j = i + 1;
		while (env[j + 1])
		{
			if (compare(env[i], env[j], false, true) > 0)
			{
				tmp = env[i];
				env[i] = env[j];
				env[j] = tmp;
			}
			j++;
		}
		tmp = join_str("declare -x ", env[x], 1, NULL);
		attach_node(&info->head_export, tmp);
		x++;
		i++;
	}
}
