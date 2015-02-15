#include <stdio.h>

int main(void)
{
	int a[] = {1,2,3,4};
	int *p = a;

	printf("a+n : %p, %p, %p, %p\n", a+0, a+1, a+2, a+3);
	printf("p+n : %p, %p, %p, %p\n", p+0, p+1, p+2, p+3);

	return 0;
}				
