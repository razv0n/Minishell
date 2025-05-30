/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yezzemry <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 11:59:19 by yezzemry          #+#    #+#             */
/*   Updated: 2025/05/29 11:59:39 by yezzemry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

int	parse_var(char *s)
{
	int	i;

	i = 0;
	if (!(s[i] >= 'a' && s[i] <= 'z') && !(s[i] >= 'A' && s[i] <= 'Z')
		&& !(s[i] == '_'))
		return (1);
	while (s[i] && ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z')
		|| (s[i] >= '0' && s[i] <= '9') || s[i] == '_') && (s[i] != '='))
		i++;
	if (!s[i] || s[i] == '=')
		return (0);
	return (1);
}

void	where_to_edit(xp **tmp, xp **ptr, char *s)
{
	while (*tmp)
	{
		if (compare((*tmp)->str + 11, s, 1) >= 0)
			break;
		*ptr = (*tmp);
		*tmp = (*tmp)->next;
	}
}

void	add_to_export2(xp **head, xp *tmp, xp *node, xp *ptr)
{
	if (ptr)
	{
		ptr->next = node;
		node->next = tmp;
	}
	else
	{
		node->next = *head;
		*head = node;
	}
}

int	add_to_export(xp **head, char *s, t_info *info)
{
	xp	*tmp;
	xp	*node;
	xp	*ptr;

	if (parse_var(s))
	{
		ft_putstr_fd("bash: export: `", 2);
		ft_putstr_fd(s, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		info->ext = 1;
		return 0;
	}
	tmp = *head;
	ptr = NULL;
	where_to_edit(&tmp, &ptr, s);
	node = malloc(sizeof(xp));
	if (!node)
		return 0; //allocation failed
	node->str = join_str("declare -x ", s);
	if (!node->str)
		return 0; //allocation failed
	node->next = NULL;
	add_to_export2(head, tmp, node, ptr);
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
	while (env[i])
	{
		j = i + 1;
		while (env[j])
		{
			if (compare(env[i], env[j], 0) > 0)
			{
				tmp = env[i];
				env[i] = env[j];
				env[j] = tmp;
			}
			j++;
		}
		tmp = join_str("declare -x ", env[x]);
		create_node(&info->head_export, tmp);
		x++;
		i++;
	}
}
