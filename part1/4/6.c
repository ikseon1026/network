#include <stdio.h>

int main(void)
{
	int b = 1;
	int *bp = &b;

	printf("b size : %lu\n", (unsigned long)sizeof(b));
	printf("&bp : %p\n", &bp);
	printf("bp  : %p\n", bp);
	printf("(int *)bp  + 1 : %p\n", bp + 1);
	printf("(int *)bp  + 2 : %p\n", bp + 2);

	printf("(char *)bp  + 1 : %p\n", (char *)bp + 1);
	printf("(char *)bp  + 2 : %p\n", (char *)bp + 2);

	return 0;
}				
