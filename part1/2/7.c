#include <stdio.h>

int sum(int a, int b);

int main(void)
{
	printf(" 3 + 4 = %d\n", sum(3, 4));	
	return 0;
}				

int sum(int a, int b)
{
	return a + b;
}
