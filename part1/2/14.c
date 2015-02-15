#include <stdio.h>

#define MAX(x,y) (x>y)?(x):(y)
#define	DOUBLE(x) x*2

int main(void)
{
	printf("MAX(3,5) : %d\n", MAX(3,5));
	printf("DOUBLE(5) : %d\n", DOUBLE(5));
	printf("DOUBLE(3+2) : %d\n", DOUBLE(3+2));

	return 0;
}				
