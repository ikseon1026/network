#include <stdio.h>

int main(void)
{
	char a = 1;
	
	char *b;
	b = &a;

	printf("&a : %p\n", &a);
	printf("b : %p\n", b);

	printf("a : %d\n", a);	
	printf("*b : %d\n", *b);	

	*b = 100;

	printf("a : %d\n", a);	
	printf("*b : %d\n", *b);	
	
	return 0;
}				
