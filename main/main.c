#include "../Minishell.h"


void    print_stack(t_list *head)
{
    while(head)
    {
        printf("%s\n",head->content);
        head = head->next;
    }
}
void    setup_signals()
{
    rl_catch_signals = 0;
    signal(SIGINT, handle_sig);
    signal(SIGQUIT, handle_sig);
}

char    *best_prompt()
{
        char cwd[1024];
        char *user;
        char prompt[1024];
        size_t size;
        char    *str;

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
        str = ft_strdup(prompt);
        return (str);
}

void    minishell_loop(t_info *info)
{
    char *str;

    while (1)
    {
        str = best_prompt();
        info->line = readline(str); // pwd  usr
        free(str);
        if (!info->line)
        {
            ft_free_all(info);
            printf("exit\n");
            exit(0);
        }
        if(info->line[0])
            add_history(info->line);
        if (pars(info) == -1) // ? dont forget to free the head after usi
            continue ;
        // print_stack(info->head_cmd);
        init_things(info, info->head_cmd);
    }
}

int main (int ac , char **av, char **env)
{
    t_info *info;

    (void) av;
    if (ac != 1)
    {
        ft_putstr_fd("minishell: cannot run this\n", 2);
        exit(1);
    }
    setup_signals();
    info = ft_malloc(sizeof(t_info));
    info->ext = 0;
    cpy_env(env, info);
    minishell_loop(info);
    ft_free(info, 1337);
}
