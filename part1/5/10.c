#include <stdio.h>

int main(void)
{
	int i, j;
	int a[6] = {1,2,3,4,5,6};
	int (*pp)[2] = (int (*)[2])a;

	for(i = 0; i < 2; i += 1) {
		for(j = 0; j < 3; j += 1) {
			printf("p[%d][%d] : %d\n", i, j, pp[i][j]);			
		}
	}
	
	return 0;
}				
