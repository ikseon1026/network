#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int a = rand();

	printf("a : %d\n", a);

	printf("a %% 100 : %d\n", a%100);
	printf("a %% 50 : %d\n", a%50);

	printf("RAND_MAX : %u\n", RAND_MAX);
		
	return 0;
}				
