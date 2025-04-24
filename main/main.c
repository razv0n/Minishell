#include "../Minishell.h"

void print_stack(t_list *head)
{
    // if (!head)
        // return ;
    while (head)
    {
        printf("head->countent %s\n",head->content);
        head = head->next;
    }
}

int main (int ac , char **av, char **env)
{
    char *line;
    t_list *head;

    head = NULL;
    (void) av;
    if (ac != 1)
    {
        printf ("minishell cannot run this\n");
        exit(1);
    }
    while (1)
    {
        line = readline("╭━━[\033[1;36mminishell\033[0m]━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╮\n╰──➤");
        if (!line)
            return (1);
        pars(line ,&head);
        print_stack(head); //for printig linked list
        free(line);
    }
    return (0);
}