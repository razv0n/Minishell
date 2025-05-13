#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>

typedef struct lsit
{
    char c;
    struct lsit *next;
}   t_list;

void    fun(t_list *head)
{
    printf("add1 : %p\n", head);
    while (head)
        head = (*head).next;
    printf("add2 : %p\n", head);
}

int main(int ac, char **av, char **env)
{
    t_list *first = malloc(sizeof(t_list));
    t_list *second = malloc(sizeof(t_list));
    t_list *third = malloc(sizeof(t_list));
    t_list *fourth = malloc(sizeof(t_list));
    t_list *head = first;
    first->next = second;
    second->next = third;
    third->next = fourth;
    fourth->next = NULL;
	fun(head);
    // printf("%d", ft_lstadd_back(&head, new));
    // int id = fork();
    // if (id == -1)
    //     return 1;
    // if (!id)
    // {
    //     // char *arg[] = {"unset", "PATH", NULL};
    //     // execve("/usr/bin/unset", arg, NULL);
    // }
    // printf("no\n");
    // cwd = NULL;
    // char cwd[] = "no way";
    // cwd[8] = 'l';
    // getcwd(cwd, 1024);
    // printf("%ld\n", sizeof(cwd));
    // free (cwd);
    // return 0;
    // char *x = readline("test ");
    // (void)x;
    // free (x);
    return 0;
}
