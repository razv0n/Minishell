#include "../Minishell.h"

int main()
{
    char **str = malloc(sizeof(char *) * 3);
    char *str_0, *str_1, *str_2;

    str[0] = malloc(sizeof(char));
    str[1] = malloc(sizeof(char));
    str[2] = malloc(sizeof(char));

    str_0 = str[0];
    str_1 = str[1];
    str_2 = str[2];
    
    free(str);
    free(str_0);
    free(str_1);
    free(str_2);

}