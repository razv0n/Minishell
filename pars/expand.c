/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 20:24:54 by mfahmi            #+#    #+#             */
/*   Updated: 2025/05/28 10:54:55 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void	ft_lstdelone(t_list *lst, void (*del) (void*))
{
	if (!del || !lst)
		return ;
	del (lst->content);
	free (lst);
}


void    remove_quotes(char **str, t_list *node)
{
    int lenght;
    char *tmp;  
    char c;

    c = *str[0];
    lenght =  ft_strlen(*str) - 2;
    tmp = *str;
    *str = ft_substr(tmp, 1, lenght);
    free(tmp);
    if (c == '\'')
        node->quotes_type = SINGLE_Q;
    else
        node->quotes_type = DOUBLE_Q;
}

char *go_to_expand (char *str)
{
    char *expand;
    
    expand = getenv(str);
    free(str);
    if (!expand)
        return (NULL);
    return (expand);
}
char    *cas_in_expand(char *str, int *i, t_info *info)
{
    char *itoa_str;

    itoa_str = NULL;
    if (str[*i] == '?')
        itoa_str = ft_itoa(info->ext);
    return (itoa_str);
}
char    *check_to_expand(char *str , int *i, t_info *info)
{
    int start;
    char *expanded;
    
    expanded = NULL;
    start = *i + 1; // spkip the $ 
    if (!str[*i])
        return (NULL);
    if (ft_isalnum(str[*i + 1]) || str[*i + 1] == '_' || str[*i + 1] == '?')
    {
        (*i)++;
        if (ft_isalpha(str[*i]) || str[*i] == '_')
        {
            while(str[*i] && str[*i] != '?' && (ft_isalnum(str[*i]) || str[*i] == '_'))
                (*i)++;
        }
        else
            return (cas_in_expand(str, i, info));
        --(*i);
        expanded = ft_substr(str, start, *i - start + 1);
        return (go_to_expand(expanded));
    }
    else
        return (NULL);
}

void    expand_2(char **str, t_type_word wich_quote, t_info *info)
{
    int i;
    char buffer[2];
    char *tmp, *expand, *prev, *str_tmp;

    str_tmp = *str;
    if (wich_quote == SINGLE_Q) 
        return;
    i = 0;
    prev = NULL; //this
    buffer[1] = '\0';
    while(str_tmp[i])
    {
        if (str_tmp[i] != '$')
        {
            buffer[0] = str_tmp[i];
            tmp = prev;
            prev = ft_strjoin(prev, buffer);
            if (!tmp)
                free(tmp);
        }
        else
        {
            expand = check_to_expand(str_tmp, &i, info);
            tmp = prev;
            if (expand)
            {
                prev = ft_strjoin(prev, expand);
                free(tmp);
            }
            else if (str_tmp[i] == '$')
            {
                prev = ft_strjoin(prev, "$");
                free(tmp);
            }
        }
        i++;
    }
        tmp = *str;
        *str = ft_strdup(prev);
        free(tmp);
        free(prev);
}

void    expand(t_info *info)
{
    t_list *content, *next_node;
    int wich_quote;

    content = info->head_cmd;
    while (content)
    {
        wich_quote = 0;
        if (content->content[0] == '$' && !content->content[1] && content->next && content->joined && check_quotes(content->next->content[0]))
        {
            next_node = content->next;
            remove_node(&info->head_cmd, content);
            content = next_node;
            continue;
        }
        if (check_quotes(content->content[0]))
            remove_quotes(&content->content ,content); // it remove quotes if it exist
        if (ft_strchr(content->content, '$'))
            expand_2(&content->content, content->quotes_type, info);
        content = content->next;
    }
}
