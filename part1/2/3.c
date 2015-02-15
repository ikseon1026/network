#include <stdio.h>

int main(void)
{
	int i;
	int a[5] = {1,2,3,4,5};
	int b[] = {1};
	int c[5] = {1,2};
	
	for(i = 0; i < 5; i++) {
		printf("a[%d] : %d\n", i, a[i]);		
	}

	for(i = 0; i < sizeof(b)/sizeof(int); i++) {
		printf("b[%d] : %d\n", i, b[i]);		
	}

	for(i = 0; i < 5; i++) {
		printf("c[%d] : %d\n", i, c[i]);		
	}

	return 0;
}				
