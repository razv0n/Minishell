#include "../../Minishell.h"

int main()
{
    struct stat st;
    stat("/home/mfahmi/goinfre/Minishell/Minishell/minishell", &st);
    if (S_ISDIR(st.st_mode))
        printf("Is a directry\n");
    else
        printf("is a file\n");
}