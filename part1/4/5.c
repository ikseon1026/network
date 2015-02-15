#include <stdio.h>

int main(void)
{
	char a = 1;	
	char *ap = &a;

	int b = 1;
	int *bp = &b;

	printf("a size : %lu\n", (unsigned long)sizeof(a));
	printf("&ap : %p\n", &ap);
	printf("ap  : %p\n", ap);
	printf("ap - 1 : %p\n", ap - 1);
	printf("ap - 2 : %p\n", ap - 2);

	printf("b size : %lu\n", (unsigned long)sizeof(b));
	printf("&bp : %p\n", &bp);
	printf("bp  : %p\n", bp);
	printf("bp  - 1 : %p\n", bp - 1);
	printf("bp  - 2 : %p\n", bp - 2);
	
	return 0;
}				
