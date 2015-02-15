#include <stdio.h>

int main(void)
{
	int i, j;
	int a[2][5] = {{1,2,3,4,5}, {6,7,8,9,10}};

	for(i = 0; i < 2; i += 1) {
			
		for(j = 0; j < 5; j += 1) {
			printf("a[%d][%d] : %d\n", i, j, a[i][j]);		
		}
	}
	return 0;
}				
