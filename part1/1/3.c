#include <stdio.h>

int main(void)
{
	int a = 1;
	int b = 2;
	int c = 0;

	if((c = b) > a) {
		printf("(c = %d) > %d : true\n", b, a);
		printf("c : %d\n", c);
	}

	return 0;
}				
