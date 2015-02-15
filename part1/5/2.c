#include <stdio.h>

int main(void)
{
	int i;
	int a[] = {1,2,3,4};
	int *p = a;

	for(i = 0; i <= 3; i++) {
		printf("a + %d : %p\n", i, a+i);
		printf("p + %d : %p\n", i, p);
		p++;
	}

	return 0;
}				
