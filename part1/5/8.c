#include <stdio.h>

int main(void)
{
	int i, j;
	int a[2][3] = {{1,2,3},{4,5,6}};

	for(i = 0; i < 2; i += 1) {
		for(j = 0; j < 3; j += 1) {
			printf("a[%d][%d] : %p\n", i, j, &(a[i][j]));	
		}
	}

	return 0;
}				
