/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 21:25:09 by mfahmi            #+#    #+#             */
/*   Updated: 2025/06/14 15:08:40 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../Minishell.h"


int	ft_strcmp(char *line, char *str)
{
	int	i;

	i = 0;
	if (!line || !str)
		return (0);
	while (line[i] && str[i])
	{
		if (line[i] != str[i])
			return (0);
		i++;
	}
	if (line[i] || str[i])
		return (0);
	return (1);
}

void    env_to_double_pointer(t_info *info)
{
    int lenght;
    int i;
    t_list *head;

    head = info->head_env;
    i = 0;
    lenght = ft_lstsize(info->head_env);
    info->env = ft_malloc(sizeof(char *) * (lenght + 1), FIRST_P);
    while(head)
    {
        info->env[i] = head->content;
        head = head->next;
        i++;
    }
    info->env[i] = NULL;
}

void    cpy_env(char **env, t_info *info)
{
    int i;
    t_list *node;

    i = 0;
    info->head_env = NULL;
    while (env[i])
    {
        node = ft_lstnew_d(ft_strdup(env[i], FIRST_P), FIRST_P);
        ft_lstadd_back_d(&info->head_env, node);
        i++;
    }
    create_export(info, env, i);
    env_to_double_pointer(info);
}

char    *ft_getenv(char *nm_varible, t_list *env)
{
    char    *expand;
    int     lenght;

    expand = NULL;
    lenght = ft_strlen(nm_varible);
    while (env)
    {
        if (!ft_strncmp(nm_varible, env->content, lenght) && *(env->content + lenght) == '=')
        {
            expand = ft_substr(env->content, lenght + 1, ft_strlen(env->content) - lenght + 1);
            break;
        }
        env = env->next;
    }
    return (expand);
}
