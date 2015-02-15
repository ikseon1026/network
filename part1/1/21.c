#include <stdio.h>

int main(void)
{
	int i, j;

	for(i=1; i<=9; i++) {
		for(j = 2; j <= 5; j++) {
			if(i == 2) break;
			printf("%d * %d = %d\t", j, i, i*j);		
		}
		printf("\n");
	}
	return 0;
}				
