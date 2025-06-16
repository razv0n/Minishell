#include <stdio.h>
#include <stdlib.h>

int main()
{
    char *s1 = "this is bom sfsfsdf\0";
    char s2[100];
    int i =0;
    while (s1[i])
        s2[i] = s1[i++];
    printf("%s",s2);
}