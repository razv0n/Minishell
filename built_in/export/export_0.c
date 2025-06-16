/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 11:59:19 by yezzemry          #+#    #+#             */
/*   Updated: 2025/06/14 22:02:26 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

int	parse_var(char *s)
{
	int	i;

	i = 0;
	if (!ft_isalpha(s[i]) && !(s[i] == '_'))
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
		res = compare((*tmp)->str + 11, s, 1);
		if (res >= 0 && res != 200)
			return (1); // to add it in the alphabet
		else if (res == 200)
			return (-1); // to replace the value
		else if (res == -200)
			return (0); // to not add it in export
		*ptr = *tmp;
		*tmp = (*tmp)->next;
	}
	return (1);
}

void	add_to_export2(t_xp **head, t_xp *node, t_xp *ptr, int cdt)
{
	
	if (!node)
		return;	
	if (ptr)
	{
		if (ptr->next)
			node->next = ptr->next->next;
		ptr->next = node;
		node->prev = ptr;
	}
	else if (!ptr && cdt != -1)
	{
		node->next = *head;
		*head = node;
	}
	else if (!ptr && cdt == -1)
	{
		node->next = (*head)->next;
		*head = node;
	}
}

int	add_to_export(t_xp **head, char *s, t_info *info)
{
	t_xp	*tmp;
	t_xp	*node;
	t_xp	*ptr;
	int	cdt;
	int	equal;

	equal = 0;
	if (parse_var(s))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(s, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		info->ext = 1;
		return 0;
	}
	tmp = *head;
	ptr = NULL;
	cdt = where_to_edit(&tmp, &ptr, s);
	node = create_node(join_str("declare -x ", s, cdt, &equal));
	add_to_export2(head, node, ptr, cdt);
	if (!equal)
		return (0);
	return (1);
}

void	create_export(t_info *info, char **env, int i)
{
	char	*tmp;
	int	j;
	int	x;

	info->head_export = NULL;
	i = 0;
	x = 0;
	while (env[i + 1])
	{
		j = i + 1;
		while (env[j + 1])
		{
			if (compare(env[i], env[j], 0) > 0)
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
