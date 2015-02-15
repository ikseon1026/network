#include <stdio.h>

int main(void)
{
	int i, j, k;	
	int a[2][2][3] = {
		{{1,2,3},{4,5,6}},
		{{7,8,9},{10,11,12}}
	};

	printf("a : %lu\n", (unsigned long)sizeof(a));
	printf("a[0] : %lu\n", (unsigned long)sizeof(a[0]));
	printf("a[0][0] : %lu\n", (unsigned long)sizeof(a[0][0]));
	printf("a[0][0][0] : %lu\n\n", (unsigned long)sizeof(a[0][0][0]));

	for(i = 0; i < 2; i += 1) {
		for(j = 0; j < 2; j += 1) {
			for(k = 0; k < 3; k += 1) {
				printf("a[%d][%d][%d] : %d\n", i, j, k, a[i][j][k]);	
				printf(" *(*(*(a + %d)+%d))+%d : %d\n", i, j, k, *(*(*(a + i)+j))+k);
			}
		}
	}

	return 0;
}				
