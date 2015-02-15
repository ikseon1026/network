#include <stdio.h>

int main(void)
{
	int i,j;
	int n;
	int a[2][3] = {{1,2,3},{4,5,6}};
	int *p = &(a[0][0]);

	for(i = 0; i < 2; i += 1) {
		
		for(j = 0; j < 3; j += 1) {
			n = (3*i) + j;

			printf("a[%d][%d] : %d\n", i, j, a[i][j]);			
			printf("a[%d] : %d\n", n, *(p+n));
			printf("a[%d] : %d\n", n, p[n]);
		}
	}
	
	return 0;
}				
