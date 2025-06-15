/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 22:30:15 by mfahmi            #+#    #+#             */
/*   Updated: 2025/06/14 22:30:16 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

// void    print_stack(t_list *head)
// {
//     while(head)
//     {
//         printf("%s\n",head->content);
//         head = head->next;
//     }
// }

char	*best_prompt(void)
{
	char	cwd[1024];
	char	*user;
	char	prompt[1024];
	size_t	size;
	char	*str;

	size = sizeof(prompt);
	user = getenv("USER");
	if (!user)
		user = "user";
	if (!getcwd(cwd, sizeof(cwd)))
		ft_strlcpy(cwd, "unknown", sizeof(cwd));
	prompt[0] = '\0';
	ft_strlcat(prompt, "\033[1;32m", size);
	ft_strlcat(prompt, user, size);
	ft_strlcat(prompt, "@minishell ", size);
	ft_strlcat(prompt, "\033[1;34m", size);
	ft_strlcat(prompt, cwd, size);
	ft_strlcat(prompt, "\033[0m$ ", size);
	// printf("  %s\n", prompt);
	str = ft_strdup(prompt, SECOUND_P);
	return (str);
}

void	minishell_loop(t_info *info)
{
	char	*str;

	while (1)
	{
		str = best_prompt();
		info->line = readline(str);
		if (!info->line)
			ft_free_all(EXIT, 0);
		add_ptr(info->line, return_ptr(), SECOUND_P);
		if (info->line[0])
			add_history(info->line);
		if (pars(info) != -1)
			init_things(info, info->head_cmd);
		ft_free(info, 1337);
	}
}

int	main(int ac, char **av, char **env)
{
	t_info	*info;

	(void)av;
	if (ac != 1)
	{
		ft_putstr_fd("minishell: cannot run this\n", 2);
		exit(1);
	}
	setup_signals();
	info = ft_malloc(sizeof(t_info), FIRST_P);
	init_info(info);
	if (info->fd_in == -1 || info->fd_out == -1)
		ft_free_all(NORMAL, 4);
	info->ext = 0;
	cpy_env(env, info);
	minishell_loop(info);
}
