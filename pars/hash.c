#include "../Minishell.h"

void check_quotes (char *line)
{
    int i;
    int j;
    char stack[3];
    bool single_quote;
    bool double_quote;

    single_quote = false;
    double_quote = false;
    i = 0;
    j = 0;
    stack[2] = '\0';
    while (line[i])
    {
        if (line[i] == '\'' && !double_quote)
        {
            single_quote = true;
            stack[j] = line[i];
            if (j && stack[j - 1] == '\'')
            {
                ft_bzero(stack, 3);
                single_quote = false;
                j = -1;
            }
            j++;
        }
        else if (line[i] == '"' && !single_quote)
        {
            double_quote = true;
            stack[j] = line[i];
            if (j && stack[j - 1] == '"')
            {
                ft_bzero(stack, 3);
                double_quote = false;
                j = -1;
            }
            j++;
        }
        i++;
    }
    if (stack[0])
    {
        printf("Syntax error\n");
    }
}