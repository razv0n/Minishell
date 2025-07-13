/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 22:30:15 by mfahmi            #+#    #+#             */
/*   Updated: 2025/07/10 18:14:51 by mfahmi           ###   ########.fr       */
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

// int is_input_from_pipe(void)
// {
//     struct stat statbuf;
//     fstat(STDIN_FILENO, &statbuf);
//     return (S_ISFIFO(statbuf.st_mode));
// }

char	*best_prompt(void)
{
	char	cwd[4096];
	char	*user;
	char	prompt[5000];
	size_t	size;
	char	*str;

	size = sizeof(prompt);
	user = getenv("USER");
	if (!user)
		user = "user";
	if (!getcwd(cwd, sizeof(cwd)))
		ft_strlcpy(cwd, "..", sizeof(cwd));
	prompt[0] = '\0';
	ft_strlcat(prompt, "\001\033[1;32m\002", size);
	ft_strlcat(prompt, user, size);
	ft_strlcat(prompt, "@minishell:~", size);
	ft_strlcat(prompt, "\001\033[1;34m\002", size);
	ft_strlcat(prompt, cwd, size);
	ft_strlcat(prompt, "\001\033[0m\002$ ", size);
	str = ft_strdup(prompt, SECOUND_P);
	return (str);
}

void	minishell_loop(t_info *info)
{
	char	*str;

	while (1)
	{
		*(sig_varible()) = false;
		str = best_prompt();
		info->line = readline(str);
		if (!info->line)
			ft_free_all(EXIT, info->ext);
		if (init_info(info) == SYS_SUCCESS)
		{
			add_ptr(info->line, return_ptr(), SECOUND_P, FREE);
			if (info->line[0])
				add_history(info->line);
			if (pars(info) == 1)
				init_things(info, info->head_cmd);
		}
		ft_free(NORMAL);
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
	info = ft_malloc(sizeof(t_info), FIRST_P, FREE);
	info->ext = 0;
	info->cw = NULL;
	cpy_env(env, info);// how do you update env (char **) if you set it just once ?
	minishell_loop(info);
}
