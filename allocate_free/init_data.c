/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:32:59 by mfahmi            #+#    #+#             */
/*   Updated: 2025/05/04 10:02:38 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void    init_info(t_info *info, char *line, char **env)
{
    info->head_env = NULL;
    info->head_cmd = NULL;
    info->content = NULL;
    info->line = line;
    cpy_env(env, info);
}
