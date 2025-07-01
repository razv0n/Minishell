#include <stdio.h>
#include <stdlib.h>

int main()
{
	int *a;
	while (1)
		a = malloc(1000000000000000L);
}
