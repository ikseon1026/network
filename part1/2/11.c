#include <stdio.h>
#include "sum.h"

int main(void)
{
	int a = 10;
	int b = 20;

	printf("%d + %d = %d\n", a, b, sum(a, b));	
	
	return 0;
}				
