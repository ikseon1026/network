#include <stdio.h>

int main(void)
{
	char a[2][2] = {{1,2},{3,4}};
	char (*p)[2] = a;

	printf("a : %p\n", a);
	printf("p : %p\n", p);
	printf("a[0] : %p\n", a[0]);
	printf("&a[0][0] : %p\n", &a[0][0]);

	return 0;
}				
